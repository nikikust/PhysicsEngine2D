#include <GameEngine/Game/Entities/EntitiesStorage.h>


namespace game
{
    EntitiesStorage::EntitiesStorage()
    {
    }


    std::shared_ptr<game::Entity> EntitiesStorage::add_entity(game::CircleEntity&& entity)
    {
        entities_.insert({ entity.get_id(), std::make_shared<game::CircleEntity>(std::move(entity)) });

        return entities_.at(entity.get_id());
    }
    std::shared_ptr<game::Entity> EntitiesStorage::add_entity(game::PolygonEntity&& entity)
    {
        entities_.insert({ entity.get_id(), std::make_shared<game::PolygonEntity>(std::move(entity)) });

        return entities_.at(entity.get_id());
    }
    std::shared_ptr<game::Entity> EntitiesStorage::add_entity(game::ComplexEntity&& entity)
    {
        entities_.insert({ entity.get_id(), std::make_shared<game::ComplexEntity>(std::move(entity)) });

        return entities_.at(entity.get_id());
    }
    std::shared_ptr<game::Entity> EntitiesStorage::add_entity(game::GroundEntity&& entity)
    {
        entities_.insert({ entity.get_id(), std::make_shared<game::GroundEntity>(std::move(entity)) });

        return entities_.at(entity.get_id());
    }
    std::shared_ptr<game::Entity> EntitiesStorage::add_entity(game::ShipEntity&& entity)
    {
        entities_.insert({ entity.get_id(), std::make_shared<game::ShipEntity>(std::move(entity)) });

        return entities_.at(entity.get_id());
    }
    

    void EntitiesStorage::remove_entity(int32_t id)
    {
        if (entities_.contains(id))
            entities_.erase(id);
    }

    std::shared_ptr<game::Entity> EntitiesStorage::get_entity(int32_t id)
    {
        if (entities_.contains(id))
            return entities_.at(id);

        return nullptr;
    }

    const std::unordered_map<int32_t, std::shared_ptr<game::Entity>>& EntitiesStorage::get_entities() const
    {
        return entities_;
    }

    void EntitiesStorage::select_entity(const std::shared_ptr<game::Entity>& entity)
    {
        selected_entity_ = entity;
    }

    std::shared_ptr<game::Entity> EntitiesStorage::get_selected_entity() const
    {
        return selected_entity_;
    }

    void EntitiesStorage::clear()
    {
        entities_.clear();
    }
} // namespace game
