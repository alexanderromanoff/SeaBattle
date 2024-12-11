// #include "../include/Abilities/Results/ResultVisitor.h"

// void ResultVisitor::Visit(struct ScanerResult& result)
// {
//     if(result.shipsFound)
//     {
//         std::cout << result.message << "detected\n";
//     }
//     else
//     {
//         std::cout << result.message << "not found\n";
//     }
// }

// void ResultVisitor::Visit(struct ShellingResult& result)
// {

//     if(result.success)
//     {
//         std::cout << result.successMessage << "\n";
//     }
//     else
//     {
//         std::cout << result.failMessage << "\n";
//     }
// }

// void ResultVisitor::Visit(struct MassiveAttackResult& result)
// {
//     std::cout << result.message << "\n";
// }