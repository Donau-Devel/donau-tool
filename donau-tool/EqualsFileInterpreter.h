#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

namespace DonauUtils {
	namespace EqualsFileInterpreter {
		class EqualsTag {
			std::string m_name;
			std::string m_content;
		public:
			std::string getName() {
				return m_name;
			}

			std::string getContent() {
				return m_content;
			}

			void addToName(char c) {
				m_name += c;
			}

			void addToContent(char c) {
				m_content += c;
			}
		};
		
		class EqualsDocument {
			std::string m_filePath;
			std::vector<EqualsTag *> m_vector;
		public:
			EqualsDocument(std::string m_filePath) {
				this->m_filePath = m_filePath;
			}

			void parse(bool skipQuotes = false, char separator = '=', char newLineIndicator = '\n') {
				bool name{ true };

				std::ifstream iFile;
				iFile.open(m_filePath);

				if (!iFile) {
					std::cout << "EqualsFileInterpreter did not find the following document: " << "\n";
					std::cout << m_filePath << "\n";
					return;
				}

				std::noskipws(iFile);
				while (!iFile.eof()) {
					char t;
					iFile >> t;

					if (name) {
						switch (t) {
						case '=':
							name = false;
							break;
						case '\n':
							m_vector.push_back(new EqualsTag());
							break;
						case '\"':
							if (!skipQuotes) {
								if (m_vector.size() == 0) {
									m_vector.push_back(new EqualsTag());
								}

								m_vector.at(m_vector.size() - 1)->addToName(t);
							}
							break;
						default:
							if (m_vector.size() == 0) {
								m_vector.push_back(new EqualsTag());
							}

							m_vector.at(m_vector.size() - 1)->addToName(t);
							break;
						}
					}
					else {
						switch (t) {
						case '\n':
							m_vector.push_back(new EqualsTag());
							name = true;
							break;
						case '\"':
							if (!skipQuotes) {
								m_vector.at(m_vector.size() - 1)->addToContent(t);
							}
							break;
						default:
							m_vector.at(m_vector.size() - 1)->addToContent(t);
							break;
						}
					}
				}
			}

			DonauUtils::EqualsFileInterpreter::EqualsTag getTag(int index) {
				EqualsTag t = *(m_vector.at(index));
				return t;
			}

			DonauUtils::EqualsFileInterpreter::EqualsTag getTagByName(std::string name) {
				for (int i{ 0 }; i < m_vector.size(); i++) {
					if (m_vector.at(i)->getName() == name) {
						return *(m_vector.at(i));
					}
				}

				return *(new EqualsTag());
			}

			int getTagVectorSize() {
				return m_vector.size();
			}
		};
	}
}

