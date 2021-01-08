#pragma once

#include <map>

#include "Layout.hpp"
#include "Scene.hpp"
#include "UIObject.hpp"

namespace glider::ui {

class UIContainerEnumerator {
public:
  virtual ~UIContainerEnumerator() {
  }
  virtual bool nextItem(UIObject* obj) = 0;
};

class UIContainer : public UIObject {
public:
  using Ref = ReferenceTmpl<UIContainer>;

  UIContainer() = default;

  void draw() override;

  void addObject(UIObject::Ref obj);

  void removeObject(UIObject::Ref obj);

  void moveObjectToFront(UIObject::Ref obj);

  void clear();

  virtual bool isContainer() const {
    return true;
  }

  void setLayout(Layout::Ref argLayout) {
    layout = argLayout;
    // layout->fillObjects(this);
    layout->update(Pos(0, 0), size);
  }

  Layout& getLayout() {
    return *layout.get();
  }

  void updateLayout() {
    if (layout.get()) {
      layout->update(Pos(0, 0), getSize());
    }
  }

  virtual UIObject::Ref findByName(const std::string& argName);

  void moveFocusToNext();

  void enumerate(UIContainerEnumerator* enumerator);

  size_t getCount() const {
    return objLst.size();
  }

  const UIObjectsList& getObjList() const {
    return objLst;
  }

protected:
  UIObjectsList objLst;
  Layout::Ref layout;

  typedef std::map<int, UIObjectsList::iterator> IdMap;
  IdMap idMap;
  UIObjectsList mouseEnterStack;
  typedef std::map<std::string, UIObject::Ref> NameMap;
  NameMap nameMap;

  void endOfResize();

  virtual void onAddObject() {
  }
  virtual void onRemoveObject(UIObjectsList::iterator it) {
  }
  virtual void onClear() {
  }

  void onMouseLeave(const MouseEvent& me);
  void onMouseMove(const MouseEvent& me);
  void onMouseButtonDown(const MouseEvent& me);
  void onMouseButtonUp(const MouseEvent& me);
  void onMouseClick(const MouseEvent& me);
  void onMouseScroll(const MouseEvent& me);

  void onObjectResize();
  void onObjectResizeEnd();
  void onFocusGain();
  void onFocusLost();
};

}  // namespace glider::ui
