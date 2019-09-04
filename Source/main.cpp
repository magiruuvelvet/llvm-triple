#include <cstdio>
#include <string>

#include <LLVMTargetTriple.hpp>

#include <llvm/Support/CommandLine.h>

namespace opts
{
    static llvm::cl::opt<std::string> input_triple(llvm::cl::Positional,
        llvm::cl::desc("<target triple>"),
        llvm::cl::Optional);

    // --verbose, -v
    static llvm::cl::opt<bool> verbose("verbose",
        llvm::cl::desc("Print verbose target triple information."));
    static llvm::cl::alias verbose_short("v", llvm::cl::desc("Print verbose target triple information."),
        llvm::cl::aliasopt(verbose));

    // --invert
    static llvm::cl::opt<bool> invert("invert",
        llvm::cl::desc("Invert the architecture (32/64-bit) of the given target."));
}

void print(const std::string &left, const std::string &right)
{
    static constexpr auto length = 30;

    const auto spaces_to_print = length - left.length() - 1;
    const std::string spaces = ([&]{
        std::string s;
        for (auto i = 0U; i < spaces_to_print; ++i)
        {
            s.append(" ");
        }
        return s;
    })();

    std::printf("%s:%s%s\n", left.c_str(), spaces.c_str(), right.c_str());
}

inline void print(const std::string &left, bool right)
{
    print(left, right ? std::string{"yes"} : std::string{"no"});
}

int main(int argc, char **argv)
{
    llvm::cl::ParseCommandLineOptions(argc, argv, "LLVM Target Triple Parser\n", nullptr, nullptr, true);

    const std::string target = opts::input_triple.empty() ?
        LLVMTargetTriple::defaultTargetTriple() :
        opts::input_triple;
    const bool verbose = opts::verbose.getValue();
    const bool invert = opts::invert.getValue();

    // parse and normalize target triple
    LLVMTargetTriple triple(target);

    if (invert)
    {
        triple.invert();
    }

    // print basic info
    print("Triple",                     triple.triple());
    print("Valid Triple",               triple.isValidTarget());
    print("Operating System",           triple.operating_system());
    print("Operating System Version",   triple.operating_system_version());
    print("Architecture",               triple.architecture());
    print("Address Model",              triple.address_model());
    print("Vendor",                     triple.vendor());
    print("Environment",                triple.environment());
    print("Environment Version",        triple.environment_version());
    print("Endianess",                  triple.endianess());
    print("Object Format",              triple.object_format());

    // print verbose info
    if (verbose)
    {
        std::printf("\n");

        // operating system detection according to LLVM
        const auto &t = triple.tripleObj();
        print("Darwin",                 t.isOSDarwin());
        print("Mac OS X",               t.isMacOSX());
        print("iOS",                    t.isiOS());
        print("tvOS",                   t.isTvOS());
        print("watchOS",                t.isWatchOS());
        print("Android",                t.isAndroid());
        print("PlayStation 3 (LV2)",    t.getOS() == llvm::Triple::Lv2);
        print("PlayStation 4",          t.isPS4());
        print("PlayStation 4 CPU",      t.isPS4CPU());
        print("FreeBSD",                t.isOSFreeBSD());
        print("kFreeBSD",               t.isOSKFreeBSD());
        print("OpenBSD",                t.isOSOpenBSD());
        print("NetBSD",                 t.isOSNetBSD());
        print("DragonFlyBSD",           t.isOSDragonFly());
        print("Linux",                  t.isOSLinux());
        print("Minix",                  t.getOS() == llvm::Triple::Minix);
        print("Fuchsia",                t.isOSFuchsia());
        print("Solaris",                t.isOSSolaris());
        print("IAMCU",                  t.isOSIAMCU());
        print("Contiki",                t.isOSContiki());
        print("Haiku",                  t.isOSHaiku());
        print("NaCl (Native Client)",   t.isOSNaCl());
        print("AIX",                    t.isOSAIX());
        print("Ananas",                 t.getOS() == llvm::Triple::Ananas);
        print("HermitCore",             t.getOS() == llvm::Triple::HermitCore);
        print("RTEMS",                  t.getOS() == llvm::Triple::RTEMS);
        print("Hurd",                   t.isOSHurd());
        print("Windows",                t.isOSWindows());
        print("Cygwin/MinGW",           t.isOSCygMing());
        print("MSVCRT",                 t.isOSMSVCRT());
        print("WASI",                   t.isOSWASI());
        print("Emscripten",             t.isOSEmscripten());
        print("CloudABI",               t.getOS() == llvm::Triple::CloudABI);
        print("BG/P Compute-Node Kernel", t.getOS() == llvm::Triple::CNK);
        print("NVIDIA CUDA",            t.getOS() == llvm::Triple::CUDA);
        print("NVIDIA OpenCL",          t.getOS() == llvm::Triple::NVCL);
        print("AMD HSA Runtime",        t.getOS() == llvm::Triple::AMDHSA);
        print("AMD PAL Runtime",        t.getOS() == llvm::Triple::AMDPAL);
        print("Mesa 3D",                t.getOS() == llvm::Triple::Mesa3D);
        print("Unknown OS",             t.isOSUnknown());
        std::printf("\n");

        // print verbose environment info
        print("GNU",                    t.isGNUEnvironment());
        print("MSVC",                   t.isWindowsMSVCEnvironment());
        print("Cygwin",                 t.isWindowsCygwinEnvironment());
        print("GLIBC",                  t.isOSGlibc());
        print("MUSL",                   t.isMusl());
    }

    return 0;
}
