#pragma once
#include <GameEngine/Game/Entities/CircleEntity.h>
#include <GameEngine/Game/Entities/PolygonEntity.h>
#include <GameEngine/Game/Entities/ComplexEntity.h>
#include <GameEngine/Game/Entities/GroundEntity.h>
#include <GameEngine/Game/Entities/ShipEntity.h>


namespace game
{
    class EntitiesStorage
    {
    public:
        EntitiesStorage();
        EntitiesStorage(EntitiesStorage&) = delete;
        EntitiesStorage(EntitiesStorage&&) = delete;


        // --- //

        std::shared_ptr<game::Entity> add_entity(game::CircleEntity&&  entity);
        std::shared_ptr<game::Entity> add_entity(game::PolygonEntity&& entity);
        std::shared_ptr<game::Entity> add_entity(game::ComplexEntity&& entity);
        std::shared_ptr<game::Entity> add_entity(game::GroundEntity&&  entity);
        std::shared_ptr<game::Entity> add_entity(game::ShipEntity&&    entity);

        void remove_entity(int32_t id);

        std::shared_ptr<game::Entity> get_entity(int32_t id);

        const std::unordered_map<int32_t, std::shared_ptr<game::Entity>>& get_entities() const;

        void select_entity(const std::shared_ptr<game::Entity>& entity);
        std::shared_ptr<game::Entity> get_selected_entity() const;

        void clear();

    private:
        std::unordered_map<int32_t, std::shared_ptr<game::Entity>> entities_;

        std::shared_ptr<game::Entity> selected_entity_;
    };
} // namespace game
