#pragma once

#include <enchantum/enchantum.hpp>
#include <imgui.h>
#include <type_traits>

namespace ImSweet {
template <typename E>
bool EnumListBox(const char *const label, E &current_enum,
                 const std::size_t height_in_items = enchantum::count<E>) {
  static_assert(std::is_enum_v<E>);
  constexpr std::size_t item_count = enchantum::count<E>;
  const auto current_index = *enchantum::enum_to_index(current_enum);

  bool changed = false;
  if (ImGui::BeginListBox(
          label,
          ImVec2(0, ImGui::GetTextLineHeightWithSpacing() * height_in_items))) {
    for (std::size_t i = 0; i < item_count; ++i) {
      const bool is_selected = (i == current_index);
      if (ImGui::Selectable(enchantum::names<E>[i].data(), is_selected)) {
        current_enum = enchantum::values<E>[i];
        changed = true;
      }
      if (is_selected)
        ImGui::SetItemDefaultFocus();
    }
    ImGui::EndListBox();
  }

  return changed;
}

template <typename E>
bool EnumComboBox(const char *const label, const char *preview,
                  E &current_enum) {
  static_assert(std::is_enum_v<E>);

  constexpr std::size_t item_count = enchantum::count<E>;
  const auto current_index = *enchantum::enum_to_index(current_enum);

  bool changed = false;
  ImGui::BeginCombo(label, preview);
  for (std::size_t i = 0; i < item_count; ++i) {
    const bool is_selected = (i == current_index);
    if (ImGui::Selectable(enchantum::names<E>[i].data(), is_selected)) {
      current_enum = enchantum::values<E>[i];
      changed = true;
    }
    if (is_selected)
      ImGui::SetItemDefaultFocus();
  }
  ImGui::EndCombo();
  return changed;
}

template <typename E>
bool EnumRadioButton(const char *const label, E &current_enum) {
  static_assert(std::is_enum_v<E>);
  bool changed = false;
  for (const auto &[value, string] : enchantum::entries<E>) {
    if (ImGui::RadioButton(string.data(), value == current_enum)) {
      changed = true;
      current_enum = value;
    }
  }
  return changed;
}

template <typename E>
bool EnumCheckboxFlags(const char *const group_label, E &enum_flags) {
  static_assert(enchantum::is_bitflag<E>);

  auto flags = enchantum::to_underlying(enum_flags);
  bool changed = false;

  if (group_label && *group_label)
    ImGui::TextUnformatted(group_label);

  for (std::size_t i = enchantum::has_zero_flag<E>; i < enchantum::count<E>;
       ++i) {
    const auto bit = enchantum::values<E>[i];
    const auto bit_value = enchantum::to_underlying(bit);
    bool checked = (flags & bit_value) != 0;

    const char *label = enchantum::names<E>[i].data();
    if (ImGui::Checkbox(label, &checked)) {
      changed = true;
      if (checked)
        flags |= bit_value;
      else
        flags &= ~bit_value;
    }
  }

  enum_flags = static_cast<E>(flags);
  return changed;
}

} // namespace ImSweet