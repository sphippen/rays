#include <functional>
#include <cassert>
#include <vector>
#include <cstdlib>
#include <SFML/Graphics.hpp>

const int sceneHeight = 800;
const int sceneWidth = 600;

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
  }
}

int main(int argc, char* argv[])
{
  srand(time(NULL));
  sf::RenderWindow window(sf::VideoMode(sceneWidth, sceneHeight), "SFML works!"/*, sf::Style::Fullscreen*/);
  
  sf::Image tracedImage;
  tracedImage.create(sceneWidth, sceneHeight);

  sf::Texture tracedTexture;
  bool created = tracedTexture.loadFromImage(tracedImage);
  assert(created && "Couldn't create texture");

  sf::Sprite sceneSprite(tracedTexture);

  std::vector<Pixel> toUpdate;
  sf::Mutex mutex;

  ThreadData d;
  d.f = [&](Pixel p) {
    sf::Lock lock(mutex);
    toUpdate.push_back(p);
  };
  d.xMin = 0;
  d.xMax = sceneWidth;
  d.yMin = 0;
  d.yMax = sceneHeight;
  sf::Thread traceThread(renderThread, d);

  traceThread.launch();

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
  exit(0);

  // To avoid warnings
  return 0;
}