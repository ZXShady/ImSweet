#pragma once
#include <imgui.h>
#include <string_view>

namespace ImSweet {

#define IMSWEET_NO_COPY(T)         \
  T(const T&)            = delete; \
  T& operator=(const T&) = delete;


struct ID {
  IMSWEET_NO_COPY(ID)
  ID(const char* s) : ID(std::string_view(s)) {}
  ID(std::string_view s) { ImGui::PushID(s.data(), s.data() + s.size()); }
  ID(const void* p) { ImGui::PushID(p); }
  ID(int i) { ImGui::PushID(i); }
  ~ID() { ImGui::PopID(); }
};

struct StyleColor {
  IMSWEET_NO_COPY(StyleColor)
  const int count;
  StyleColor(ImGuiCol idx, const ImVec4& col) : count(1) { ImGui::PushStyleColor(idx, col); }
  StyleColor(std::initializer_list<std::pair<ImGuiCol, ImVec4>> list) : count((int)list.size())
  {
    for (const auto& [col, val] : list)
      ImGui::PushStyleColor(col, val);
  }
  ~StyleColor() { ImGui::PopStyleColor(count); }
};

struct StyleVar {
  IMSWEET_NO_COPY(StyleVar)
  const int count;
  StyleVar(ImGuiStyleVar idx, float val) : count(1) { ImGui::PushStyleVar(idx, val); }
  StyleVar(ImGuiStyleVar idx, ImVec2 val) : count(1) { ImGui::PushStyleVar(idx, val); }
  StyleVar(std::initializer_list<std::pair<ImGuiStyleVar, float>> list) : count((int)list.size())
  {
    for (const auto& [idx, val] : list)
      ImGui::PushStyleVar(idx, val);
  }
  StyleVar(std::initializer_list<std::pair<ImGuiStyleVar, ImVec2>> list) : count((int)list.size())
  {
    for (const auto& [idx, val] : list)
      ImGui::PushStyleVar(idx, val);
  }
  ~StyleVar() { ImGui::PopStyleVar(count); }
};

struct Font {
  IMSWEET_NO_COPY(Font)
  Font(ImFont* font) { ImGui::PushFont(font); }
  ~Font() { ImGui::PopFont(); }
};

struct ItemWidth {
  IMSWEET_NO_COPY(ItemWidth)
  ItemWidth(float width) { ImGui::PushItemWidth(width); }
  ~ItemWidth() { ImGui::PopItemWidth(); }
};

struct TextWrapPos {
  IMSWEET_NO_COPY(TextWrapPos)
  TextWrapPos(float wrap_pos_x = 0.0f) { ImGui::PushTextWrapPos(wrap_pos_x); }
  ~TextWrapPos() { ImGui::PopTextWrapPos(); }
};

struct ClipRect {
  IMSWEET_NO_COPY(ClipRect)
  ClipRect(ImVec2 min, ImVec2 max, bool intersect = false) { ImGui::PushClipRect(min, max, intersect); }
  ~ClipRect() { ImGui::PopClipRect(); }
};

struct AllowKeyboardFocus {
  IMSWEET_NO_COPY(AllowKeyboardFocus)
  AllowKeyboardFocus(bool allow) { ImGui::PushAllowKeyboardFocus(allow); }
  ~AllowKeyboardFocus() { ImGui::PopAllowKeyboardFocus(); }
};

struct ButtonRepeat {
  IMSWEET_NO_COPY(ButtonRepeat)
  ButtonRepeat(bool repeat = true) { ImGui::PushButtonRepeat(repeat); }
  ~ButtonRepeat() { ImGui::PopButtonRepeat(); }
};

struct Indent {
  IMSWEET_NO_COPY(Indent)
  float width;
  Indent(float w = 0.0f) : width(w) { ImGui::Indent(w); }
  ~Indent() { ImGui::Unindent(width); }
};

struct Window {
  IMSWEET_NO_COPY(Window)
  const bool opened;
  Window(const char* name, bool* p_open = nullptr, ImGuiWindowFlags flags = 0)
  : opened(ImGui::Begin(name, p_open, flags))
  {
  }
  ~Window()
  {
    if (opened)
      ImGui::End();
  }
  explicit operator bool() const { return opened; }
};

struct Child {
  IMSWEET_NO_COPY(Child)
  const bool opened;
  Child(const char* id, ImVec2 size = ImVec2(0, 0), bool border = false, ImGuiWindowFlags flags = 0)
  : opened(ImGui::BeginChild(id, size, border, flags))
  {
  }
  ~Child()
  {
    if (opened)
      ImGui::EndChild();
  }
  explicit operator bool() const { return opened; }
};

struct ChildFrame {
  IMSWEET_NO_COPY(ChildFrame)
  const bool opened;
  ChildFrame(ImGuiID id, ImVec2 size, ImGuiWindowFlags flags = 0) : opened(ImGui::BeginChildFrame(id, size, flags)) {}
  ~ChildFrame()
  {
    if (opened)
      ImGui::EndChildFrame();
  }
  explicit operator bool() const { return opened; }
};

struct Combo {
  IMSWEET_NO_COPY(Combo)
  const bool opened;
  Combo(const char* label, const char* preview, ImGuiComboFlags flags = 0)
  : opened(ImGui::BeginCombo(label, preview, flags))
  {
  }
  ~Combo()
  {
    if (opened)
      ImGui::EndCombo();
  }
  explicit operator bool() const { return opened; }
};

struct ListBox {
  IMSWEET_NO_COPY(ListBox)
  const bool opened;
  ListBox(const char* label, ImVec2 size = ImVec2(0, 0)) : opened(ImGui::BeginListBox(label, size)) {}
  ~ListBox()
  {
    if (opened)
      ImGui::EndListBox();
  }
  explicit operator bool() const { return opened; }
};

struct MenuBar {
  IMSWEET_NO_COPY(MenuBar)
  const bool opened;
  MenuBar() : opened(ImGui::BeginMenuBar()) {}
  ~MenuBar()
  {
    if (opened)
      ImGui::EndMenuBar();
  }
  explicit operator bool() const { return opened; }
};

struct MainMenuBar {
  IMSWEET_NO_COPY(MainMenuBar)
  const bool opened;
  MainMenuBar() : opened(ImGui::BeginMainMenuBar()) {}
  ~MainMenuBar()
  {
    if (opened)
      ImGui::EndMainMenuBar();
  }
  explicit operator bool() const { return opened; }
};

struct Menu {
  IMSWEET_NO_COPY(Menu)
  const bool opened;
  Menu(const char* label, bool enabled = true) : opened(ImGui::BeginMenu(label, enabled)) {}
  ~Menu()
  {
    if (opened)
      ImGui::EndMenu();
  }
  explicit operator bool() const { return opened; }
};

struct Popup {
  IMSWEET_NO_COPY(Popup)
  const bool opened;
  Popup(const char* str_id, ImGuiWindowFlags flags = 0) : opened(ImGui::BeginPopup(str_id, flags)) {}
  ~Popup()
  {
    if (opened)
      ImGui::EndPopup();
  }
  explicit operator bool() const { return opened; }
};

struct PopupModal {
  IMSWEET_NO_COPY(PopupModal)
  const bool opened;
  PopupModal(const char* name, bool* p_open = nullptr, ImGuiWindowFlags flags = 0)
  : opened(ImGui::BeginPopupModal(name, p_open, flags))
  {
  }
  ~PopupModal()
  {
    if (opened)
      ImGui::EndPopup();
  }
  explicit operator bool() const { return opened; }
};

struct PopupContextItem {
  IMSWEET_NO_COPY(PopupContextItem)
  const bool opened;
  PopupContextItem(const char* str_id = nullptr, ImGuiPopupFlags flags = 1)
  : opened(ImGui::BeginPopupContextItem(str_id, flags))
  {
  }
  ~PopupContextItem()
  {
    if (opened)
      ImGui::EndPopup();
  }
  explicit operator bool() const { return opened; }
};

struct PopupContextWindow {
  IMSWEET_NO_COPY(PopupContextWindow)
  const bool opened;
  PopupContextWindow(const char* str_id = nullptr, ImGuiPopupFlags flags = 1)
  : opened(ImGui::BeginPopupContextWindow(str_id, flags))
  {
  }
  ~PopupContextWindow()
  {
    if (opened)
      ImGui::EndPopup();
  }
  explicit operator bool() const { return opened; }
};

struct PopupContextVoid {
  IMSWEET_NO_COPY(PopupContextVoid)
  const bool opened;
  PopupContextVoid(const char* str_id = nullptr, ImGuiPopupFlags flags = 1)
  : opened(ImGui::BeginPopupContextVoid(str_id, flags))
  {
  }
  ~PopupContextVoid()
  {
    if (opened)
      ImGui::EndPopup();
  }
  explicit operator bool() const { return opened; }
};

struct DragDropSource {
  IMSWEET_NO_COPY(DragDropSource)
  const bool opened;
  DragDropSource(ImGuiDragDropFlags flags = 0) : opened(ImGui::BeginDragDropSource(flags)) {}
  ~DragDropSource()
  {
    if (opened)
      ImGui::EndDragDropSource();
  }
  explicit operator bool() const { return opened; }
};

struct DragDropTarget {
  IMSWEET_NO_COPY(DragDropTarget)
  const bool opened;
  DragDropTarget() : opened(ImGui::BeginDragDropTarget()) {}
  ~DragDropTarget()
  {
    if (opened)
      ImGui::EndDragDropTarget();
  }
  explicit operator bool() const { return opened; }
};

struct Group {
  IMSWEET_NO_COPY(Group)
  Group() { ImGui::BeginGroup(); }
  ~Group() { ImGui::EndGroup(); }
};

struct Tooltip {
  IMSWEET_NO_COPY(Tooltip)
  Tooltip() { ImGui::BeginTooltip(); }
  ~Tooltip() { ImGui::EndTooltip(); }
};

struct Disabled {
  IMSWEET_NO_COPY(Disabled)
  Disabled() { ImGui::BeginDisabled(); }
  ~Disabled() { ImGui::EndDisabled(); }
};

struct TreeNode {
  IMSWEET_NO_COPY(TreeNode)
  const bool opened;
  TreeNode(const char* label, ImGuiTreeNodeFlags flags = 0) : opened(ImGui::TreeNodeEx(label, flags)) {}
  ~TreeNode()
  {
    if (opened)
      ImGui::TreePop();
  }
  explicit operator bool() const { return opened; }
};

struct TabBar {
  IMSWEET_NO_COPY(TabBar)
  const bool opened;
  TabBar(const char* id, ImGuiTabBarFlags flags = 0) : opened(ImGui::BeginTabBar(id, flags)) {}
  ~TabBar()
  {
    if (opened)
      ImGui::EndTabBar();
  }
  explicit operator bool() const { return opened; }
};

struct TabItem {
  IMSWEET_NO_COPY(TabItem)
  const bool opened;
  TabItem(const char* label, bool* p_open = nullptr, ImGuiTabItemFlags flags = 0)
  : opened(ImGui::BeginTabItem(label, p_open, flags))
  {
  }
  ~TabItem()
  {
    if (opened)
      ImGui::EndTabItem();
  }
  explicit operator bool() const { return opened; }
};

struct Table {
  IMSWEET_NO_COPY(Table)
  const bool opened;
  Table(const char* id, int columns, ImGuiTableFlags flags = 0, ImVec2 size = {}, float inner_width = 0)
  : opened(ImGui::BeginTable(id, columns, flags, size, inner_width))
  {
  }
  ~Table()
  {
    if (opened)
      ImGui::EndTable();
  }
  explicit operator bool() const { return opened; }
};

#undef IMSWEET_NO_COPY

} // namespace ImSweet
