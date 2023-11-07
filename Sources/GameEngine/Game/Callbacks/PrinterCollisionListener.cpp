#include <GameEngine/Game/Callbacks/PrinterCollisionListener.h>


namespace game
{
    void PrinterCollisionListener::begin_contact(physics::CollisionContact& contact)
    {
        std::cout << "Fixtues " << contact.fixture_A->get_id() << " and " 
                                << contact.fixture_B->get_id() << " collided!" << std::endl;
    }

    void PrinterCollisionListener::end_contact(physics::CollisionContact& contact)
    {
        std::cout << "Fixtues " << contact.fixture_A->get_id() << " and " 
                                << contact.fixture_B->get_id() << " no more colliding!" << std::endl;
    }
} // namespace game
