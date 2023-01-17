#include <iostream>
#include <chrono>
#include <Compilation/Compiler.hpp>
#include <Core/VirtualMachine.hpp>
#include <Utilities/File.hpp>
#include <Modules/ModuleLoader.hpp>
#include <Modules/SystemModule.hpp>

using namespace VoltLang;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::microseconds;

int main(int argc, char **argv)
{
    Object obj;
    std::cout << "Size of Object  " << sizeof(obj) << std::endl;
    std::cout << "Offset of type  " << offsetof(Object, type) << std::endl;
    std::cout << "Offset of union " << offsetof(Object, as_uint64) << std::endl;
    

    return 0;

    std::string filepath = "fibonacci.asm";

    if(argc > 1)
    {
        filepath = std::string(argv[1]);
    }

    if(!File::Exists(filepath))
    {
        std::cout << "The file does not exist " << filepath << std::endl;
        return 1;
    }

    ModuleLoader::Load<SystemModule>();

    std::string source = File::ReadAllText(filepath);

    Compiler compiler;
    Assembly assembly;
    VirtualMachine machine;

    if(compiler.Compile(source, &assembly))
    {
        if(machine.LoadAssembly(&assembly))
        {
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
    }

    return 0;
}