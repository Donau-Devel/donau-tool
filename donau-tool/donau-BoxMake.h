#pragma once

#include "Console.h"
#include <vector>
#include <string>

namespace DonauUtils {
	namespace BoxMake {
		const std::string bm_warning{ "warning" };
		const std::string bm_information{ "info" };
		const std::string bm_question{ "question" };

		class Box {
			std::string name;
			std::vector<std::string> content;
			std::string type;

		public:
			Box(std::string name, std::string type) {
				this->name = name;
				this->type = type;
			}

			Box(std::string name, std::vector<std::string> content, std::string type) {
				this->content = content;
				Box(name, type);
			}

			Box(std::string name, std::string content, std::string type) {
				this->content.push_back(content);
				Box(name, type);
			}

			~Box()
			{
			}

			void setName(std::string name) {
				this->name = name;
			}

			std::string getName() {
				return this->name;
			}

			void setContent(std::vector<std::string> content) {
				this->content = content;
			}

			void setContent(std::string content) {
				this->content.clear();
				this->content.push_back(content);
			}

			void addContent(std::string content) {
				this->content.push_back(content);
			}

			std::vector<std::string> getContent() {
				return this->content;
			}

			void setType(std::string type) {
				this->type = type;
			}

			std::string getType() {
				return this->type;
			}

			void show() {
				std::string text{ "" };
				for (int i{ 0 }; i < this->content.size(); i++) {
					text += content.at(i);
					if (i != this->content.size() - 1) {
						text += "\n";
					}
				}
				std::string call{ "zenity --" + this->type + " --title \"" + this->name + "\" --text \"" + text + "\"" };
				Console::invokeCall(call);
			}
		};
	}
}
