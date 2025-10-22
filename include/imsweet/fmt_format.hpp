#pragma once
#include <fmt/format.h>
#include <imgui.h>

namespace ImSweet {
namespace fmt {

template <typename... Args>
void Text(const fmt::format_string<Args...> fmt, Args &&...args) {
  const auto text = fmt::format(fmt, static_cast<Args &&>(args)...);
  ImGui::TextUnformatted(text.data(), text.data() + text.size());
}
template <typename... Args>
void TextColored(const ImVec4 color, const fmt::format_string<Args...> fmt,
                 Args &&...args) {
  const auto text = fmt::format(fmt, static_cast<Args &&>(args)...);
  ImGui::PushStyleColor(ImGuiCol_Text, color);
  ImGui::TextUnformatted(text.data(), text.data() + text.size());
  ImGui::PopStyleColor();
}

template <typename... Args>
void TextDisabled(const fmt::format_string<Args...> fmt, Args &&...args) {
  return TextColored(ImGui::GetStyleColorVec4(ImGuiCol_TextDisabled), fmt,
                     static_cast<Args &&>(args)...);
}

template <typename... Args>
void BulletText(fmt::format_string<Args...> fmt, Args &&...args) {
  const auto text = fmt::format(fmt, static_cast<Args &&>(args)...);
  ImGui::BulletText("%s", text.c_str());
}

template <typename... Args>
void LabelText(const char *label, fmt::format_string<Args...> fmt,
               Args &&...args) {
  const auto text = fmt::format(fmt, static_cast<Args &&>(args)...);
  ImGui::LabelText(label, "%s", text.c_str());
}

template <typename... Args>
void TextWrapped(fmt::format_string<Args...> fmt, Args &&...args) {
  const auto text = fmt::format(fmt, static_cast<Args &&>(args)...);
  ImGui::TextWrapped("%s", text.c_str());
}

template <typename... Args>
void SetTooltip(fmt::format_string<Args...> fmt, Args &&...args) {
  if (ImGui::IsItemHovered()) {
    const auto text = fmt::format(fmt, static_cast<Args &&>(args)...);
    ImGui::BeginTooltip();
    ImGui::TextUnformatted(text.data(), text.data() + text.size());
    ImGui::EndTooltip();
  }
}
} // namespace fmt

} // namespace ImSweet