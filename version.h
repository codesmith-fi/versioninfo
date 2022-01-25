#ifndef __VERSIONINFO_H_DEFINED__
#define __VERSIONINFO_H_DEFINED__
#include <iostream>
#include <cstdint>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <exception>

namespace codesmith {
    namespace types {
        class Version
        {
        public:
            Version() : Version(0, 0, 1) {
            }

            Version(
                uint16_t verMajor,
                uint16_t verMinor,
                uint16_t verBuild )
                : m_major(verMajor),
                  m_minor(verMinor),
                  m_build(verBuild) {
            }

            virtual ~Version() { }

            void set(uint16_t major, uint16_t minor, uint16_t build) {
                m_major = major;
                m_minor = minor;
                m_build = build;
            }

            void incrementMajor() {
                m_major++;
                m_minor = 0;
                m_build = 1;
            }

            void incrementMinor() {
                m_minor++;
                m_build = 1;
            }

            void incrementBuild() {
                m_build++;
            }

            void setMajor(uint16_t newMajor) {
                m_major = newMajor;
            }

            void setMinor(uint16_t newMinor) {
                m_minor = newMinor;
            }

            void setBuild(uint16_t newBuild) {
                m_build = newBuild;
            }

            uint16_t getMajor() const { return m_major; }
            uint16_t getMinor() const { return m_minor; }
            uint16_t getBuild() const { return m_build; }

            std::string str() const {
                std::stringstream os;
                os << m_major << "." << m_minor << " Build " << m_build;
                return os.str();
            }

            void save() const {
                try {
                    std::ofstream version_file;
                    version_file.open(VERSION_FILENAME, std::ios::out | std::ios::binary);

                    uint32_t major = reversebytes32(m_major);
                    uint32_t minor = reversebytes32(m_minor);
                    uint32_t build = reversebytes32(m_build);
                    version_file.write((char*)&major, sizeof(uint32_t));
                    version_file.write((char*)&minor, sizeof(uint32_t));
                    version_file.write((char*)&build, sizeof(uint32_t));
                    version_file.close();
                }
                catch (std::exception& e) {
                    std::cerr << "Fatal: " << e.what() << std::endl;
                }
            }

            void load() {
                try {
                    std::ifstream version_file;
                    version_file.open(VERSION_FILENAME, std::ios::in | std::ios::binary);
                    version_file.read((char*)&m_major, sizeof(uint32_t));
                    version_file.read((char*)&m_minor, sizeof(uint32_t));
                    version_file.read((char*)&m_build, sizeof(uint32_t));
                    m_major = reversebytes32(m_major);
                    m_minor = reversebytes32(m_minor);
                    m_build = reversebytes32(m_build);
                    version_file.close();
                }
                catch(std::exception& e) {
                    std::cerr << "Fatal: " << e.what() << std::endl;
                }
            }

        private:
            uint32_t reversebytes32(uint32_t num) const {
                uint32_t result = num;
                if(!is_big_endian()) {
                    result = (num >> 24) & 0x000000ff |
                        (num >> 8) & 0x0000ff00 |
                        (num << 8) & 0x00ff0000 |
                        (num << 24) & 0xff000000;
                }
                return result;
            }

            bool is_big_endian(void) const
            {
                union {
                    uint32_t i;
                    char c[4];
                } bint = { 0x01020304 };

                return bint.c[0] == 1;
            }
        private:
            inline static const std::string VERSION_FILENAME = "version.dat";
            uint32_t m_major;
            uint32_t m_minor;
            uint32_t m_build;
        };
    } // namespace types
} // namespace codesmith

#endif //__VERSIONINFO_H_DEFINED__
