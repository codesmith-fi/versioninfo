#ifndef __VERSIONINFO_H_DEFINED__
#define __VERSIONINFO_H_DEFINED__
#include <cstdint>
#include <string>
#include <sstream>

template< class T >
class VersionInfoBase
{
public:
    VersionInfoBase() : VersionInfoBase(0,0,1) {
    }

    VersionInfoBase(
        T verMajor,
        T verMinor,
        T verBuild) 
            : m_major(verMajor), 
                m_minor(verMinor), 
                m_build(verBuild) { 
        }

    virtual ~VersionInfoBase() { }

    void set(T major, T minor, T build) {
        m_major = major;
        m_minor = minor;
        m_build = build;
    }

    void incrementMajor() {
        m_major++;
    }

    void incrementMinor() {
        m_minor++;
    }

    void incrementBuild() {
        m_build++;
    }

    void setMajor(T newMajor) {
        m_major = newMajor;
    }

    void setMinor(T newMinor) {
        m_minor = newMinor;
    }

    void setBuild(T newBuild) {
        m_build = newBuild;
    }

    T getMajor() const { return m_major; }
    T getMinor() const { return m_minor; }
    T getBuild() const { return m_build; }

    std::string getString() const {
        std::stringstream os;
        os << m_major << "." << m_minor << " Build " << m_build;      
        return os.str();
    }

private:
        uint16_t m_major;
        uint16_t m_minor;
        uint16_t m_build;
};

typedef VersionInfoBase<uint8_t> Version8;
typedef VersionInfoBase<uint16_t> Version16;
typedef VersionInfoBase<uint32_t> Version32;

#endif //__VERSIONINFO_H_DEFINED__
