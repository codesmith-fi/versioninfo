#ifndef __CMDLINE_H_DEFINED__
#define __CMDLINE_H_DEFINED__

#include <vector>
#include <string>

namespace codesmith {
	namespace util {
		class CommandLineOption {
		public:
			CommandLineOption(const std::string keyword, const std::string help, bool required = false)
				: m_keyword(keyword), m_helpText(help), m_required(required) { };
			virtual ~CommandLineOption() { };

			const std::string& keyword() const { return m_keyword; };
			const std::string& helpText() const { return m_helpText; };
		private:
			std::string m_keyword;
			std::string m_helpText;
			bool m_required;
		};

		class CommandLineArgs {
		public:
			CommandLineArgs(int argc, char** argv) {
				for (auto i = 0; i < argc; ++i) {
					std::string opt(argv[i]);
					m_args.emplace_back(opt);
				}
			}

			virtual ~CommandLineArgs() { };

			void addOption(const CommandLineOption& option) {
				m_options.emplace_back(option);
			}

			void showHelp() const {
				for (const CommandLineOption opt : m_options) {
					std::cout << "  " << opt.keyword() << "\t\t" << opt.helpText() << "\n";
				}
			}

			bool optionExists(const CommandLineOption& option) const {
				bool result = false;
				for(const std::string& arg : m_args) {
					if(option.keyword().compare(arg) == 0) {
						result = true;
						break;
					}
				}
				return result;
			}

			const std::string getValueStr(const CommandLineOption& option) const {
				for (auto i = 0; i < m_args.size(); ++i) {
					if (option.keyword().compare(m_args[i]) == 0) {
						if (i < m_args.size() - 1) {
							return m_args[i + 1];
						}
					}
				}
				return "";
			}

			int getValueInt(const CommandLineOption& option) const {
				std::string strValue = getValueStr(option);
				int intValue = std::strtol(strValue.c_str(), nullptr, 10);
				
				return intValue;
			}

		private:
			std::vector<std::string> m_args;
			std::vector<CommandLineOption> m_options;
			std::string m_value;
		};
	} // namespace util
} // namespace codesmith

#endif // __CMDLINE_H_DEFINED__