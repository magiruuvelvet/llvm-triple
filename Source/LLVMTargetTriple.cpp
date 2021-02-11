#include "LLVMTargetTriple.hpp"

#include <sstream>

LLVMTargetTriple::LLVMTargetTriple(const std::string_view &triple)
{
    // parse and normalize target triple
    this->_triple.setTriple(triple.data());
    this->_triple.setTriple(this->_triple.normalize());
}

bool LLVMTargetTriple::isValidTarget() const
{
    // target is only valid if the operating system and architecture is known
    return
        _triple.getOS() != llvm::Triple::UnknownOS &&
        _triple.getArch() != llvm::Triple::UnknownArch;
}

void LLVMTargetTriple::invert()
{
    if (_triple.isArch32Bit())
    {
        _triple = _triple.get64BitArchVariant();
    }
    else if (_triple.isArch64Bit())
    {
        _triple = _triple.get32BitArchVariant();
    }
}

const std::string LLVMTargetTriple::operating_system() const
{
    // LLVM prints everything in lowercase, use a custom mapping with pretty printing
    switch (_triple.getOS())
    {
        case llvm::Triple::UnknownOS:   return "unknown";
        case llvm::Triple::Ananas:      return "Ananas";
        case llvm::Triple::CloudABI:    return "CloudABI";
        case llvm::Triple::Darwin:      return "Darwin";
        case llvm::Triple::DragonFly:   return "DragonFlyBSD";
        case llvm::Triple::FreeBSD:     return "FreeBSD";
        case llvm::Triple::Fuchsia:     return "Google Fuchsia";
        case llvm::Triple::IOS:         return "Apple iOS";
        case llvm::Triple::KFreeBSD:    return "Debian GNU/kFreeBSD";
        case llvm::Triple::Linux:       return "Linux";
        case llvm::Triple::Lv2:         return "Sony PlayStation 3 (LV2)";
        case llvm::Triple::MacOSX:      return "Apple Mac OS X";
        case llvm::Triple::NetBSD:      return "NetBSD";
        case llvm::Triple::OpenBSD:     return "OpenBSD";
        case llvm::Triple::Solaris:     return "Solaris";
        case llvm::Triple::Win32:       return "Microsoft Windows";
        case llvm::Triple::Haiku:       return "Haiku OS";
        case llvm::Triple::Minix:       return "Minix";
        case llvm::Triple::RTEMS:       return "RTEMS";
        case llvm::Triple::NaCl:        return "Native Client";
        case llvm::Triple::CNK:         return "BG/P Compute-Node Kernel";
        case llvm::Triple::AIX:         return "IBM AIX";
        case llvm::Triple::CUDA:        return "NVIDIA CUDA";
        case llvm::Triple::NVCL:        return "NVIDIA OpenCL";
        case llvm::Triple::AMDHSA:      return "AMD HSA Runtime";
        case llvm::Triple::PS4:         return "Sony PlayStation 4 (Orbis OS)";
        case llvm::Triple::ELFIAMCU:    return "IAMCU";
        case llvm::Triple::TvOS:        return "Apple tvOS";
        case llvm::Triple::WatchOS:     return "Apple watchOS";
        case llvm::Triple::Mesa3D:      return "Mesa 3D";
        case llvm::Triple::Contiki:     return "Contiki";
        case llvm::Triple::AMDPAL:      return "AMD PAL Runtime";
        case llvm::Triple::HermitCore:  return "HermitCore Unikernel/Multikernel";
        case llvm::Triple::Hurd:        return "GNU/Hurd";
        case llvm::Triple::WASI:        return "WebAssembly System Interface";
        case llvm::Triple::Emscripten:  return "Emscripten";
    }
    return "unknown";
}

const std::string LLVMTargetTriple::operating_system_version() const
{
    unsigned major{0}, minor{0}, micro{0};
    _triple.getOSVersion(major, minor, micro);

    if (major == 0 && minor == 0 && micro == 0)
    {
        return "unspecified";
    }
    else
    {
        std::stringstream version;
        version << major << '.' << minor << '.' << micro;
        return version.str();
    }
}

const std::string LLVMTargetTriple::vendor() const
{
    // LLVM prints everything in lowercase, use a custom mapping with pretty printing
    switch (_triple.getVendor())
    {
        case llvm::Triple::UnknownVendor:       return "unknown";
        case llvm::Triple::Apple:               return "Apple";
        case llvm::Triple::PC:                  return "Generic PC";
        case llvm::Triple::SCEI:                return "Sony Computer Entertainment, Inc.";
        case llvm::Triple::BGP:                 return "BGP";
        case llvm::Triple::BGQ:                 return "BGQ";
        case llvm::Triple::Freescale:           return "Freescale";
        case llvm::Triple::IBM:                 return "IBM";
        case llvm::Triple::ImaginationTechnologies: return "Imagination Technologies";
        case llvm::Triple::MipsTechnologies:    return "Mips Technologies";
        case llvm::Triple::NVIDIA:              return "NVIDIA";
        case llvm::Triple::CSR:                 return "CSR";
        case llvm::Triple::Myriad:              return "Myriad";
        case llvm::Triple::AMD:                 return "Advanced Micro Devices";
        case llvm::Triple::Mesa:                return "Mesa";
        case llvm::Triple::SUSE:                return "SUSE";
        case llvm::Triple::OpenEmbedded:        return "OpenEmbedded";
    }
    return "unknown";
}

const std::string LLVMTargetTriple::environment() const
{
    switch (_triple.getEnvironment())
    {
        case llvm::Triple::UnknownEnvironment: return "unknown";
        case llvm::Triple::GNU:         return "GNU";
        case llvm::Triple::GNUABIN32:   return "GNU ABI Itanium 32";
        case llvm::Triple::GNUABI64:    return "GNU ABI64";
        case llvm::Triple::GNUEABI:     return "GNU EABI (soft-float)";
        case llvm::Triple::GNUEABIHF:   return "GNU EABI (hard-float)";
        case llvm::Triple::GNUX32:      return "GNU x32";
        case llvm::Triple::CODE16:      return "Code16";
        case llvm::Triple::EABI:        return "EABI (soft-float)";
        case llvm::Triple::EABIHF:      return "EABI (hard-float)";
        //case llvm::Triple::ELFv1:       return "ELF v1";
        //case llvm::Triple::ELFv2:       return "ELF v2";
        case llvm::Triple::Android:     return "Android";
        case llvm::Triple::Musl:        return "musl libc";
        case llvm::Triple::MuslEABI:    return "musl libc (EABI soft-float)";
        case llvm::Triple::MuslEABIHF:  return "musl libc (EABI hard-float)";
        case llvm::Triple::MSVC:        return "Microsoft Visual C/C++ Runtime";
        case llvm::Triple::Itanium:     return "Itanium";
        case llvm::Triple::Cygnus:      return "Cygnus";
        case llvm::Triple::CoreCLR:     return "Microsoft .NET Core Runtime (CoreCLR)";
        case llvm::Triple::Simulator:   return "Simulator";
        case llvm::Triple::MacABI:      return "Mac Catalyst";
    }
    return "unknown";
}

const std::string LLVMTargetTriple::environment_version() const
{
    unsigned major{0}, minor{0}, micro{0};
    _triple.getEnvironmentVersion(major, minor, micro);

    if (major == 0 && minor == 0 && micro == 0)
    {
        return "unspecified";
    }
    else
    {
        std::stringstream version;
        version << major << '.' << minor << '.' << micro;
        return version.str();
    }
}

const std::string LLVMTargetTriple::endianess() const
{
    // make sure unknown is returned on an invalid triple
    if (_triple.getArch() == llvm::Triple::UnknownArch)
    {
        return "unknown";
    }

    return _triple.isLittleEndian() ? "Little Endian" : "Big Endian";
}

const std::string LLVMTargetTriple::object_format() const
{
    // make sure unknown is returned on an invalid triple
    if (_triple.getOS() == llvm::Triple::UnknownOS)
    {
        return "unknown";
    }

    switch (_triple.getObjectFormat())
    {
        case llvm::Triple::UnknownObjectFormat: return "unknown";
        case llvm::Triple::COFF:                return "COFF";
        case llvm::Triple::ELF:                 return "ELF";
        case llvm::Triple::MachO:               return "Mach-O";
        case llvm::Triple::Wasm:                return "WebAssembly";
        case llvm::Triple::XCOFF:               return "XCOFF";
    }
    return "unknown";
}

const std::string LLVMTargetTriple::address_model() const
{
    if (_triple.isArch16Bit())
    {
        return "16-bit";
    }
    else if (_triple.isArch32Bit())
    {
        return "32-bit";
    }
    else if (_triple.isArch64Bit())
    {
        return "64-bit";
    }
    else
    {
        return "unknown";
    }
}
