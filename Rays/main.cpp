#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <functional>
#include <vector>
#include <memory>

#include <SFML/Graphics.hpp>

#include "World.h"

using std::vector;
using std::shared_ptr;
using std::make_shared;

const int sceneHeight = 1080;
const int sceneWidth = 1920;

struct Pixel
{
  int x;
  int y;
  double r;
  double g;
  double b;
};

typedef std::function<void (Pixel)> PixelCallback;
struct ThreadData
{
  PixelCallback f;
  int xMin;
  int xMax;
  int yMin;
  int yMax;
};

void renderThread(ThreadData d)
{
  // Right now it's just one thread, we'll have to change the World class for multithreading
  // if we go that route
  spr::World w;
  w.build();
  w.render_scene(d.xMax - d.xMin, d.yMax - d.yMin);
  // TODO: hook up world to pixel callback
  /*
  for (int y = d.yMin; y < d.yMax; ++y) {
    for (int x = d.xMin; x < d.xMax; ++x) {
      Pixel p;
      p.x = x;
      p.y = y;
      p.r = 0;
      p.g = 0;
      p.b = 0;
      p.r += static_cast<double>(x) / sceneWidth;
      p.g += 1.0 - static_cast<double>(y) / sceneHeight;
      p.b += sin(static_cast<double>(x+y) / (sceneWidth + sceneHeight));
      d.f(p);
    }
  }*/
}

int main(int argc, char* argv[])
{
  srand(time(NULL));
  sf::RenderWindow window(sf::VideoMode(sceneWidth, sceneHeight), "SFML works!", sf::Style::Fullscreen);
  
  sf::Image tracedImage;
  tracedImage.create(sceneWidth, sceneHeight);

  sf::Texture tracedTexture;
  bool created = tracedTexture.loadFromImage(tracedImage);
  assert(created && "Couldn't create texture");

  sf::Sprite sceneSprite(tracedTexture);

  vector<Pixel> toUpdate;
  sf::Mutex mutex;

  ThreadData d;
  d.f = [&](Pixel p) {
    sf::Lock lock(mutex);
    toUpdate.push_back(p);
  };

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