#include <iostream>
#include <Compilation/Compiler.hpp>
#include <IO/File.hpp>
#include <Compilation/Instruction.hpp>
#include <Core/VirtualMachine.hpp>
#include <Core/Assembly.hpp>
#include <Core/StandardLibrary.hpp>
#include <chrono>

using namespace VoltLang;

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::microseconds;

int main(int argc, char** argv)
{
    StandardLibrary::Initialize();

    Assembly assembly;
    VirtualMachine machine;

    std::string filepath = "fibonacci.vlt";

    if (!File::Exists(filepath))
    {
        std::cout << "File does not exist: " << filepath << std::endl;
        return 1;
    }

    std::string source = File::ReadAllText(filepath);

    Compiler compiler;

    if(compiler.Compile(source, &assembly))
    {
        machine.LoadAssembly(&assembly);

        ExecutionStatus status = ExecutionStatus::Ok;

        auto startTime = high_resolution_clock::now();

        while (status == ExecutionStatus::Ok)
        {
            status = machine.Run();
        }

        auto endTime = high_resolution_clock::now();
        auto elapsedMilliseconds = duration_cast<microseconds>(endTime - startTime).count() * 0.001;

        std::cout << "Execution finished with status " << (int)status << " in " << elapsedMilliseconds << " milliseconds" << std::endl;
    }

    return 0;
}