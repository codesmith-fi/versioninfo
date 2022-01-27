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
					std::cout << "matching \"" << arg << "\" with \"" << option.keyword() << "\"\n";
					if(option.keyword().compare(arg) == 0) {
						result = true;
						break;
					}
				}
				return result;
			}
		private:
			std::vector<std::string> m_args;
			std::vector<CommandLineOption> m_options;
		};
	} // namespace util
} // namespace codesmith

#endif // __CMDLINE_H_DEFINED__