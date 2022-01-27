#ifndef __CMDLINE_H_DEFINED__
#define __CMDLINE_H_DEFINED__

#include <vector>
#include <string>

namespace codesmith {
	namespace util {
		class CommandLineOption {
		public:
			CommandLineOption(const std::string keyword, bool required = false)
				: m_keyword(keyword), m_required(required) { };
			virtual ~CommandLineOption() { };

			const std::string& keyword() const { return m_keyword; };
		private:
			std::string m_keyword;
			bool m_required;
		};

		class CommandLineArgs {
		public:
			CommandLineArgs(int argc, char** argv) {
				for(auto i = 0; i < argc; ++i) {
					std::string opt(argv[i]);
					m_args.emplace_back(opt);
				}
			}

			virtual ~CommandLineArgs() { };

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
		};
	} // namespace util
} // namespace codesmith

#endif // __CMDLINE_H_DEFINED__