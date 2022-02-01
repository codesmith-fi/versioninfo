/**
Utility classes to handle command line arguments. This is a early
version.

Author: Erno Pakarinen(codesmith.fi@gmail.com)
Date : 31.01.2022

See usage from 'versioninfo.cpp'. But basically you create a
instance of CommandLineArgs class passing the system argc and argv
parameters. Example:

	codesmith::util::CommandLineArgs args(argc, argv);

Then add the expected options using

	codesmith::util::CommandLineOption optionHelp("-h",
		"Show this help information");
	args.addOption(optionInit);
	...

Arguments can be checked and retrieved with following methods
	
	if(args.optionExists(optionHelp)) {
	    ... show help
	}

Get numeric option value:

	int majorver = args.getValueInt(optionMajorVer);

Get string option value:

	std::string initStr = getValueStr(optionInit);

Note! This version does not support arguments which have spaces, e.g.
"This is a argument" is not supported. Only simple flags and values are
supported.

LICENSE - MIT
Copyright(c) 2022 Erno Pakarinen(codesmith.fi@gmail.com)

Permission is hereby granted, free of charge, to any person obtaining
a copy of this softwareand associated documentation files(the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and /or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions :

The above copyright noticeand this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

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
				for (auto i = 0; i < (int)m_args.size(); ++i) {
					if (option.keyword().compare(m_args[i]) == 0) {
						if (i < ((int)m_args.size() - 1)) {
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