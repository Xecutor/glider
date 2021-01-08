#include <stdio.h>

#include "Button.hpp"
#include "EditInput.hpp"
#include "Engine.hpp"
#include "EventCallback.hpp"
#include "Label.hpp"
#include "Layout.hpp"
#include "ListBox.hpp"
#include "ResourcesManager.hpp"
#include "ScrollBar.hpp"
#include "UIConfig.hpp"
#include "UIContainer.hpp"
#include "UIRoot.hpp"
#include "Window.hpp"

using namespace glider;
using namespace glider::ui;

class Test : public Managed {
public:
  void method() {
    printf("hello\n");
  }
  void method2(const int& x) {
    printf("x=%d\n", x);
  }

  void test() {
    auto eh = MKCALLBACK(method);
    eh();
  }
};

class ScrollEventHandler : public Managed {
protected:
  Label::Ref lbl;

public:
  ScrollEventHandler(ScrollBar* scr, Label::Ref argLbl) : lbl(argLbl) {
    scr->setValueChangeHandler(MKUICALLBACK(onValueChanged));
  }
  void onValueChanged(const UIEvent& evt) {
    lbl->setCaption(FORMAT("value:%{}", (int)((ScrollBar*)evt.sender)->getValue()));
  }
};

int cnt = 0;

void onClick(Button::Ref b, const UIEvent& e) {
  char buf[32];
  sprintf(buf, "test%d", cnt++);
  b->setCaption(buf);
}

void onClick2(const UIEvent& e) {
  glider::engine.exitApp();
}

void onClick3(Window::Ref w, const UIEvent& e) {
  w->setVisible(!w->isVisible());
}

void addClick(Window::Ref w, const UIEvent& e) {
  static int cnt = 0;
  auto lb = w->findByName("lb").as<ListBox>();
  auto l = MakeRef<Label>(FORMAT("one more %{}", cnt++));
  l->setColor(glider::Color::black);
  lb->addObject(l);
}

int GliderAppMain(int argc, char* argv[]) {
  // Test t;
  // t.test();

  kst::Logger::Init("uitest.log");
  try {
    using namespace glider;
    using namespace glider::ui;
    engine.setVSync(true);
    engine.selectResolution(1024, 768, false);
    engine.setClearColor(Color(0, 0, 0, 0.5));
    // engine.selectResolution(800,480,false);
    engine.setResolution();
    engine.setDefaultFont(manager.getFont("FreeMono.ttf" /*"FSEX300.ttf"*/, 16));
    uiConfig.init();

    engine.assignHandler(root);
    auto b = MakeRef<Button>();
    b->setEventHandler(betOnClick, [b](const auto& event) { onClick(b, event); });
    b->setName("button1");
    b->setCaption("test");
    b->setPos(Pos(100, 100));
    root->addObject(b);

    auto b2 = MakeRef<Button>();
    b2->setName("button2");
    b2->setCaption("Quit");
    b2->setPos(Pos(100, 100 + b->getSize().y + 5));
    b2->setEventHandler(betOnClick, onClick2);
    root->addObject(b2);

    auto w3 = MakeRef<Window>(Pos(400, 400), Pos(300, 300), "scroller test");
    {
      auto lb = MakeRef<ListBox>();
      lb->setName("lb");
      lb->setSize(Pos(200, 200));
      lb->setPos(Pos(1, 1));
      auto l = MakeRef<Label>("hello");
      l->setColor(Color::black);
      lb->addObject(l);
      l = MakeRef<Label>("world");
      l->setColor(Color::black);
      lb->addObject(l);
      l = MakeRef<Label>("lalala");
      l->setColor(Color::black);
      lb->addObject(l);
      w3->addObject(lb);
      auto b = MakeRef<Button>("Add");
      b->setPos(Pos(202, 1));
      b->setEventHandler(betOnClick, [w3](const auto& evt) { addClick(w3, evt); });
      w3->addObject(b);
    }
    // ScrollBar* sb=new ScrollBar(100);
    // Label* ll=new Label;
    // ScrollEventHandler seh(sb,ll);
    // w3->addObject(sb);
    // w3->addObject(ll);
    root->addObject(w3);

    auto w = MakeRef<Window>(Pos(200, 200), Pos(200, 200), "window title");
    auto l = MakeRef<Layout>("XLCC");
    auto b3a = MakeRef<Button>();
    b3a->setName("button3a");
    b3a->setCaption("hello3a");
    l->add(b3a);
    w->addObject(b3a);
    auto b3b = MakeRef<Button>();
    b3b->setName("button3b");
    b3b->setCaption("hello3b");
    l->add(b3b);
    w->addObject(b3b);
    auto lbl = MakeRef<Label>("hello!");
    l->add(lbl);
    w->addObject(lbl);

    l->update(Pos(0, 0), w->getSize());
    w->setSize(l->getSize() + Pos(0.0f, (float)w->getTitleHeight()));
    w->setLayout(l);
    w->setResizable(false);

    root->addObject(w);

    auto w2 = MakeRef<Window>(Pos(500, 200), Pos(200, 200), "xxAxx other title");
    auto b4 = MakeRef<Button>();
    b4->setName("button4");
    b4->setCaption("hello4");
    b4->setPos(Pos(10, 20));
    w2->addObject(b4);
    auto b5 = MakeRef<Button>();
    b5->setName("button5");
    b5->setCaption("hello5");
    b5->setEventHandler(betOnClick, [w](const auto& evt) { onClick3(w, evt); });
    b5->setPos(Pos(10, 60));
    w2->addObject(b5);
    auto ed = MakeRef<EditInput>();
    ed->setValue("hello world");
    ed->setPos(Pos(10, 90));
    w2->addObject(ed);
    root->addObject(w2);

    // printf("%s\n",b->getFullName().c_str());

    engine.loop(root);
    // engine.loop(&b);
  } catch (std::exception& e) {
    fprintf(stderr, "Exception: %s\n", e.what());
    LOGERROR("main", "Exception:%{}", e.what());
  }
  uiConfig.shutdown();
  return 0;
}
