#pragma once

#include "Label.hpp"
#include "Rectangle.hpp"
#include "Text.hpp"
#include "UIContainer.hpp"

namespace glider::ui {

class Window : public UIContainer {
public:
  using Ref = ReferenceTmpl<Window>;
  Window(const Pos& argPos = Pos(0, 0), const Pos& argSize = Pos(500, 300), std::string_view argTitle = {});
  void draw();
  void setTitle(std::string_view argTitle) {
    titleText->setCaption(argTitle);
  }
  void addObject(UIObject::Ref obj) {
    client->addObject(obj);
  }
  void setLayout(Layout::Ref argLayout) {
    client->setLayout(argLayout);
  }
  Layout& getLayout() {
    return client->getLayout();
  }
  int getTitleHeight() const {
    return (int)title->rect.getSize().y;
  }
  Pos getClientSize() const {
    return size - Pos(0.0f, (float)getTitleHeight());
  }
  void setClientSize(const Pos& argSize) {
    setSize(argSize + Pos(0.0f, (float)getTitleHeight()));
  }
  void setResizable(bool argValue);

  virtual UIObject::Ref findByName(const std::string& argName) {
    return client->findByName(argName);
  }
  void setFocus() {
    client->setFocus();
  }

protected:
  class WindowTitle : public UIContainer {
  public:
    using Ref = ReferenceTmpl<WindowTitle>;
    WindowTitle() : dragging(false) {
    }
    void draw();
    void onObjectResize();
    Rectangle rect;
    bool dragging;
    void onMouseButtonDown(const MouseEvent& me);
    void onMouseButtonUp(const MouseEvent& me);
    void onMouseMove(const MouseEvent& me);
  };
  class WindowClient : public UIContainer {
  public:
    using Ref = ReferenceTmpl<WindowClient>;
    void draw();
    void onObjectResize();
    Rectangle rect;
  };
  WindowTitle::Ref title;
  WindowClient::Ref client;
  Label::Ref titleText;
  Rectangle::Ref frame;
  Rectangle::Ref resizer;
  bool resizing;
  bool resizable;
  void onMouseButtonDown(const MouseEvent& me);
  void onMouseButtonUp(const MouseEvent& me);
  void onMouseMove(const MouseEvent& me);
  void onObjectResize();
  void onFocusGain();
  void onFocusLost();
};

}  // namespace glider::ui
