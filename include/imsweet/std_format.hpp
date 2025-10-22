#pragma once
#include <imgui.h>
#include <format>

namespace ImSweet {
	template<typename... Args>
	void Text(const std::format_string<Args...> fmt, Args&&... args) {
		const auto text = std::format(fmt, static_cast<Args&&>(args)...);
		ImGui::TextUnformatted(text.data(), text.data() + text.size());
	}

	template<typename... Args>
	void TextColored(const ImVec4 color, const std::format_string<Args...> fmt, Args&&... args) {
		const auto text = std::format(fmt, static_cast<Args&&>(args)...);
		ImGui::PushStyleColor(ImGuiCol_Text, color);
		ImGui::TextUnformatted(text.data(), text.data() + text.size());
		ImGui::PopStyleColor();
	}

	template<typename... Args>
	void TextDisabled(const std::format_string<Args...> fmt, Args&&... args) {
		return TextColored(ImGui::GetStyleColorVec4(ImGuiCol_TextDisabled), fmt, static_cast<Args&&>(args)...);
	}

	template<typename... Args>
	void BulletText(std::format_string<Args...> fmt, Args&&... args) {
		const auto text = std::format(fmt, static_cast<Args&&>(args)...);
		ImGui::BulletText("%s", text.c_str());
	}

	template<typename... Args>
	void LabelText(const char* label, std::format_string<Args...> fmt, Args&&... args) {
		const auto text = std::format(fmt, static_cast<Args&&>(args)...);
		ImGui::LabelText(label, "%s", text.c_str());
	}

	template<typename... Args>
	void TextWrapped(std::format_string<Args...> fmt, Args&&... args) {
		const auto text = std::format(fmt, static_cast<Args&&>(args)...);
		ImGui::TextWrapped("%s", text.c_str());
	}

	template<typename... Args>
	void SetTooltip(std::format_string<Args...> fmt, Args&&... args) {
		if (ImGui::IsItemHovered()) {
			const auto text = std::format(fmt, static_cast<Args&&>(args)...);
			ImGui::BeginTooltip();
			ImGui::TextUnformatted(text.data(), text.data() + text.size());
			ImGui::EndTooltip();
		}
	}
}