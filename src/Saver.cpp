#include "../include/Game/SaveLoad/Saver.h"
#include "../include/Players/UserPlayer.h"
#include "../include/Players/DummyPlayer.h"


using json = nlohmann::json;


    std::ostream& operator<<(std::ostream& os, GameState& gState) 
    {
        json jUser;
        json jDummy;
        json jHash;
        StringOperator stringOp;
        SimpleEncryptor encryptor;

        UserPlayer& user = *gState.getUser();
        jUser["userFieldHeight"] = user.getField().getHeight();
        jUser["userFieldWidth"] = user.getField().getWidth();
        jUser["userFieldState"] = stringOp.toStringField(user.getField());
        jUser["userShips"] = stringOp.toStringShips(user.getField());
        jUser["userAbilities"] = stringOp.toStringAbMan(user.getAbManager());
        jUser["userProps"] = stringOp.toStringProperties(user.getProperties());
        
        DummyPlayer& dummy = *gState.getDummy();
        jDummy["dummyFieldHeight"] = dummy.getField().getHeight();
        jDummy["dummyFieldWidth"] = dummy.getField().getWidth();
        jDummy["dummyFieldState"] = stringOp.toStringField(dummy.getField());
        jDummy["dummyShips"] = stringOp.toStringShips(dummy.getField());
        jDummy["dummyProps"] = stringOp.toStringProperties(dummy.getProperties());


        std::string serializedData = jUser.dump() + jDummy.dump();
        jHash["hash"] = encryptor.hash(serializedData);
        
        os << jUser.dump() << "\n";
        os << jDummy.dump() << "\n"; 
        os << jHash.dump();
        return os;
    }

    std::istream& operator>>(std::istream& is, GameState& gState) {
        
        std::string userData;
        std::string dummyData;
        std::string hash;
        std::getline(is, userData);
        std::getline(is, dummyData);
        std::getline(is, hash);

        json jUser = json::parse(userData);
        json jDummy = json::parse(dummyData);
        json jHash = json::parse(hash);

        StringOperator stringOp;
        SimpleEncryptor encryptor;

        std::string serializedData = jUser.dump() + jDummy.dump();

        unsigned long presentHash = encryptor.hash(serializedData);
        unsigned long trueHash = jHash["hash"].get<unsigned long>();

        if(trueHash != presentHash)
        {
            std::cout << "file was changed\n";
            return is;
        }

        UserPlayer* user = gState.getUser();
        
        int height = jUser["userFieldHeight"].get<int>();
        int width = jUser["userFieldWidth"].get<int>();

        Field& uField = *(new Field(height, width));
        ShipManager& uShipMan = *(new ShipManager);
        AbilityManager& uAbMan = *(new AbilityManager);

        uField = stringOp.initFromStringField(jUser["userFieldState"].get<std::string>(), uField);
        uShipMan =stringOp.initFromStringShips(jUser["userShips"].get<std::string>(), uField, uShipMan);
        uAbMan = stringOp.initFromStringAbMan(jUser["userAbilities"].get<std::string>(), uAbMan);

        user->initUser(&uField, &uShipMan, &uAbMan);

        DummyPlayer* dummy = gState.getDummy();

        height = jDummy["dummyFieldHeight"].get<int>();
        width = jDummy["dummyFieldWidth"].get<int>();

        Field& dField = *(new Field(height, width));
        ShipManager& dShipMan = *(new ShipManager);

        dField = stringOp.initFromStringField(jDummy["dummyFieldState"].get<std::string>(), dField);
        dShipMan = stringOp.initFromStringShips(jDummy["dummyShips"].get<std::string>(), dField, dShipMan);

        dummy->initDummy(&dField, &dShipMan);

        return is;
    }

    Saver::Saver(std::string destination) : destination(destination) {}

    void Saver::save(GameState& gState) {
        std::ofstream ofs(destination);
        if (ofs.is_open()) 
        {
            ofs << gState; 
            ofs.close();
        } 
        else 
        {
            throw std::runtime_error("Unable to open file for saving.");
        }
    }

    void Saver::load(GameState& gState) {
        std::ifstream ifs(destination);
        if (ifs.is_open()) 
        {
            ifs >> gState; 
            ifs.close();
        } 
        else 
        {
            throw std::runtime_error("Unable to open file for loading.");
        }
    }

