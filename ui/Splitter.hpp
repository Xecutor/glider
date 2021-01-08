/*
 * Splitter.hpp
 *
 *  Created on: 11 ����. 2016 �.
 *      Author: konst
 */

#ifndef SRC_UI_SPLITTER_HPP_
#define SRC_UI_SPLITTER_HPP_

#include "Rectangle.hpp"
#include "UIContainer.hpp"

namespace glider {
namespace ui {

class Splitter : public UIContainer {
public:
  enum SplitterOrientation { soHorizontal, soVertical };
  enum ResizePolicy { rpProportional, rpKeepFirst, rpKeepSecond };
  Splitter(SplitterOrientation argOrientation, int argPosition);
  void setFirst(UIObject::Ref obj);
  void setSecond(UIObject::Ref obj);
  void setPosition(int argPosition);
  int getPosition() const {
    return position;
  }
  void setResizePolicy(ResizePolicy argResizePolicy) {
    resizePolicy = argResizePolicy;
  }
  SplitterOrientation getOrientation() const {
    return orientation;
  }

protected:
  SplitterOrientation orientation;
  ResizePolicy resizePolicy = rpProportional;
  UIObject::Ref first, second;
  struct SplitterRect : public UIObject {
    Rectangle rect;
    void draw() {
      rect.draw();
    }
    void onMouseButtonDown(const MouseEvent& me);
    void onMouseButtonUp(const MouseEvent& me);
    void onMouseMove(const MouseEvent& me);
    bool resizing = false;
    Posi<int> resStart;
    int startPos;
  };
  ReferenceTmpl<SplitterRect> sRect;
  int position;
  int splitterWidth;
  int minFirstWidth;
  int minSecondWidth;
  virtual void onObjectResize();
  virtual void onObjectResizeEnd();

  virtual void onParentResize();
  virtual void onParentResizeEnd();

  void recalcPosition();

  void updateFirstPosAndSize();
  void updateSecondPosAndSize();
};

}  // namespace ui
}  // namespace glider

#endif /* SRC_UI_SPLITTER_HPP_ */
