#pragma once
#include <GameEngine/Game/Entities/CircleEntity.h>
#include <GameEngine/Game/Entities/PolygonEntity.h>
#include <GameEngine/Game/Entities/ComplexEntity.h>
#include <GameEngine/Game/Entities/GroundEntity.h>


namespace game
{
    class EntitiesStorage
    {
    public:
        EntitiesStorage();
        EntitiesStorage(EntitiesStorage&) = delete;
        EntitiesStorage(EntitiesStorage&&) = delete;


        // --- //

        std::shared_ptr<game::Entity> add_entity(game::CircleEntity  entity);
        std::shared_ptr<game::Entity> add_entity(game::PolygonEntity entity);
        std::shared_ptr<game::Entity> add_entity(game::ComplexEntity entity);
        std::shared_ptr<game::Entity> add_entity(game::GroundEntity  entity);

        void remove_entity(int32_t id);

        std::shared_ptr<game::Entity> get_entity(int32_t id);

        const std::unordered_map<int32_t, std::shared_ptr<game::Entity>>& get_entities() const;

    private:
        std::unordered_map<int32_t, std::shared_ptr<game::Entity>> entities_;

    };
} // namespace game
