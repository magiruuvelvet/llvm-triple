#ifndef LLVMTARGETTRIPLE_HPP
#define LLVMTARGETTRIPLE_HPP

#include <string>
#include <string_view>

#include <llvm/Config/llvm-config.h>
#include <llvm/ADT/Triple.h>

class LLVMTargetTriple
{
public:
    LLVMTargetTriple(const std::string_view &triple);

    // returns the default target triple this LLVM installation was configured for
    static const std::string defaultTargetTriple()
    {
        return LLVM_DEFAULT_TARGET_TRIPLE;
    }

    bool isValidTarget() const;

    // Invert the architecture (32/64-bit) of the target triple
    void invert();

    // parsed and normalized target triple
    // may not match with the input
    inline const std::string &triple() const
    { return _triple.getTriple(); }

    // detected operating system
    const std::string operating_system() const;

    // detected operating system version
    const std::string operating_system_version() const;

    // detected architecture
    inline const std::string architecture() const
    { return _triple.getArchTypeName(_triple.getArch()); }

    // detected hardware vendor
    const std::string vendor() const;

    // detected environment
    const std::string environment() const;
    //{ return _triple.getEnvironmentTypeName(_triple.getEnvironment()); }

    // detected environment version
    const std::string environment_version() const;

    // target system endianess
    const std::string endianess() const;

    // operating system object format
    const std::string object_format() const;

    // processor address model
    const std::string address_model() const;

    // returns a const reference to the underlying llvm::Triple instance
    const llvm::Triple &tripleObj() const
    { return _triple; }

private:
    llvm::Triple _triple;

};

#endif // LLVMTARGETTRIPLE_HPP
