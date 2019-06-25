//Ported from donauctl

#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>

namespace DonauUtils {
	namespace XMLParseDX {
		class XMLTag {
		private:
			std::string m_name;
			std::string m_value;
			bool m_isFinished{ false };
		public:
			XMLTag(std::string name, std::string value)
				: m_name(name), m_value(value)
			{
			}

			XMLTag(std::string name) : m_name(name)
			{
			}

			XMLTag()
			{
			}

			void setName(std::string name) {
				m_name = name;
			}

			void updateName(std::string name) {
				m_name = m_name + name;
			}

			void updateName(char name) {
				m_name = m_name + name;
			}

			std::string getName() {
				return m_name;
			}

			void setValue(std::string value) {
				m_value = value;
			}

			void updateValue(std::string value) {
				m_value = m_value + value;
			}

			void updateValue(char value) {
				m_value = m_value + value;
			}

			std::string getValue() {
				return m_value;
			}

			void setFinished(bool setTo) {
				m_isFinished = setTo;
			}

			void setFinished(int setTo) {
				m_isFinished = setTo;
			}

			bool getFinished() {
				return m_isFinished;
			}
		};

		class XMLDocument {
		private:
			std::ifstream m_iFile;
			std::vector<DonauUtils::XMLParseDX::XMLTag> m_xmlTags;

			void m_resizeTags(int howMany = 1) {
				m_xmlTags.resize(m_xmlTags.size() + howMany);
			}

			void m_addTag() {
				m_resizeTags();
			}

			void m_addTag(std::string name) {
				m_resizeTags();
				m_xmlTags.at(m_xmlTags.size() - 1).setName(name);
			}

			void m_addTag(std::string name, std::string value) {
				m_resizeTags();
				m_xmlTags.at(m_xmlTags.size() - 1).setName(name);
				m_xmlTags.at(m_xmlTags.size() - 1).setValue(value);
			}

			void m_addValueToLatestUnfinished(char toAdd, std::string searchName) {
				for (unsigned long i{ m_xmlTags.size() - 1 }; i > 0; i--) {
					if (m_xmlTags.at(i).getName() == searchName &&
						!m_xmlTags.at(i).getFinished()) {
						m_xmlTags.at(i).updateValue(toAdd);
						break;
					}
				}
			}

			void m_addValueToLatestUnfinished(char toAdd) {
				for (unsigned long i{ m_xmlTags.size() - 1 }; i > 0; i--) {
					if (!m_xmlTags.at(i).getFinished()) {
						m_xmlTags.at(i).updateValue(toAdd);
						break;
					}
				}
			}

			void m_finishTagByName(std::string searchName) {
				for (unsigned long i{ m_xmlTags.size() - 1 }; i > 0; i--) {
					if (m_xmlTags.at(i).getName() == searchName &&
						!m_xmlTags.at(i).getFinished()) {
						m_xmlTags.at(i).setFinished(true);
						break;
					}
				}
			}
		public:
			XMLDocument(std::string fileName) {
				m_iFile.open(fileName);
				if (!m_iFile) {
					std::cerr << "XMLParseDX could not find: " << fileName << "\n";
					std::cerr << "Program will now close.\n";
					exit(0);
				}
				else {
					m_addTag("donau-XMLParseDX-root", "");
				}
			}

			void doNotIgnoreWhitespace() {
				m_iFile >> std::noskipws;
			}

			void ignoreWhitespace() {
				m_iFile >> std::skipws;
			}

			DonauUtils::XMLParseDX::XMLTag getFirstElementByName(std::string name) {
				for (int i{ 0 }; i < m_xmlTags.size(); i++) {
					if (m_xmlTags.at(i).getName() == name) {
						return m_xmlTags.at(i);
					}
				}
				return m_xmlTags.at(0);
			}

			int getFirstElementPositionByName(std::string name) {
				for (int i{ 0 }; i < m_xmlTags.size(); i++) {
					if (m_xmlTags.at(i).getName() == name) {
						return i;
					}
				}
				return 0;
			}

			DonauUtils::XMLParseDX::XMLTag getElementByValue(std::string value) {
				for (int i{ 0 }; i < m_xmlTags.size(); i++) {
					if (m_xmlTags.at(i).getValue() == value) {
						return m_xmlTags.at(i);
					}
				}
				return m_xmlTags.at(0);
			}

			void parse() {
				int parseState{ 0 }; //check parseState.txt on host machine
				char currentChar;
				std::string savedName = "";
				while (!m_iFile.eof()) {
					m_iFile >> currentChar;
					switch (parseState) {
					case 0:
						switch (currentChar) {
						case '<':
							parseState = 1;
							break;
						default:
							m_addValueToLatestUnfinished(currentChar);
							break;
						}
						break;
					case 1:
						switch (currentChar) {
						case '/':
							parseState = 2;
							break;
						case '?':
							m_addTag();
							parseState = 3;
							break;
						default:
							m_addTag();
							parseState = 4;
							switch (currentChar) {
							case '>':
								parseState = 0;
								break;
							default:
								m_xmlTags.at(m_xmlTags.size() - 1).updateName(currentChar);
								break;
							}
							break;
						}
						break;
					case 2:
						switch (currentChar) {
						case '>':
							m_finishTagByName(savedName);
							savedName = "";
							parseState = 0;
							break;
						default:
							savedName += currentChar;
							break;
						}
						break;
					case 3:
						switch (currentChar) {
						case '>':
							parseState = 0;
							break;
						case '?':
							break;
						default:
							m_xmlTags.at(m_xmlTags.size() - 1).updateName(currentChar);
							break;
						}
						break;
					case 4:
						switch (currentChar) {
						case '>':
							parseState = 0;
							break;
						default:
							m_xmlTags.at(m_xmlTags.size() - 1).updateName(currentChar);
							break;
						}
						break;
					default:
						//DonauBackend::echo("Error! Cannot continue as the value of parse state is incorrect.");
						break;
					}
				}
				m_xmlTags.at(m_xmlTags.size() - 1).setFinished(true);
				m_xmlTags.at(0).setFinished(true);
			}

			DonauUtils::XMLParseDX::XMLTag getTag(int tagNumber) {
				return m_xmlTags.at(tagNumber);
			}

			int getTagVectorSize() {
				return m_xmlTags.size();
			}

		};
	}
}