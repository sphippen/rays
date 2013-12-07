#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <functional>
#include <vector>
#include <memory>

#include <SFML/Graphics.hpp>

#include "World.h"
#include "Vec3.h"

using std::vector;
using std::shared_ptr;
using std::make_shared;

const int sceneHeight = 200;
const int sceneWidth = 200;

struct Pixel
{
  int x;
  int y;
  double r;
  double g;
  double b;
};

typedef std::function<void (int x, int y, spr::Vec3 color)> PixelCallback;
struct ThreadData
{
  PixelCallback f;
  spr::World* w;
  int xMin;
  int xMax;
  int yMin;
  int yMax;
};

void renderThread(ThreadData d)
{
  d.w->render_scene(d.xMin, d.xMax, d.yMin, d.yMax, d.f);
}

int main(int argc, char* argv[])
{
  sf::RenderWindow window(sf::VideoMode(sceneWidth, sceneHeight), "Rays" /*, sf::Style::Fullscreen*/);
  
  sf::Image tracedImage;
  tracedImage.create(sceneWidth, sceneHeight);

  sf::Texture tracedTexture;
  bool created = tracedTexture.loadFromImage(tracedImage);
  assert(created && "Couldn't create texture");

  sf::Sprite sceneSprite(tracedTexture);

  vector<Pixel> toUpdate;
  sf::Mutex mutex;
  
  spr::World w;
  w.build(sceneWidth, sceneHeight);

  ThreadData d;
  d.f = [&](int x, int y, spr::Vec3 color) {
    Pixel p;
    p.x = x;
    // The ray tracer has y=0 on the bottom, but sf::Image has y=0 on the top, so we reverse it here
    p.y = sceneHeight - 1 - y;
    p.r = color.x;
    p.g = color.y;
    p.b = color.z;
    sf::Lock lock(mutex);
    toUpdate.push_back(p);
  };
  d.w = &w;

  vector<shared_ptr<sf::Thread>> threads;
  const int xDiv = 1;
  const int yDiv = 1;
  for (int x = 0; x < xDiv; ++x) {
    for (int y = 0; y < yDiv; ++y) {
      d.xMin = (x * sceneWidth) / xDiv;
      d.xMax = ((x+1) * sceneWidth) / xDiv;
      d.yMin = (y * sceneHeight) / yDiv;
      d.yMax = ((y+1) * sceneHeight) / yDiv;
      auto thread = make_shared<sf::Thread>(renderThread, d);
      thread->launch();
      threads.push_back(thread);
    }
  }

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
      else if (event.type == sf::Event::KeyPressed) {
        bool altf4 = (event.key.code == sf::Keyboard::F4) && (event.key.alt);
        bool esc = event.key.code == sf::Keyboard::Escape;
        if (altf4 || esc)
          window.close();
      }
    }

    std::vector<Pixel> local;
    {
      sf::Lock lock(mutex);
      local = toUpdate;
      toUpdate.clear();
    }

    for (auto itr = begin(local); itr != end(local); ++itr) {
      Pixel p = *itr;
      sf::Uint8 color[] = {static_cast<sf::Uint8>(255*p.r), static_cast<sf::Uint8>(255*p.g), static_cast<sf::Uint8>(255*p.b), 255};
      tracedImage.setPixel(p.x, p.y, sf::Color(color[0], color[1], color[2], color[3]));
    }
    tracedTexture.update(tracedImage);

    window.clear();
    window.draw(sceneSprite);
    window.display();
  }
  // Exit early to avoid waiting for any created threads to finish (sf::Thread destructor waits)
  exit(0);

  // To avoid warnings
  return 0;
}