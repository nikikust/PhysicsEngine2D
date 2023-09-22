#include <GameEngine/Game/Entities/EntitiesStorage.h>


namespace game
{
    EntitiesStorage::EntitiesStorage()
    {
    }


    std::shared_ptr<game::Entity> EntitiesStorage::add_entity(game::CircleEntity entity)
    {
        entities_.insert({ entity.get_id(), std::make_shared<game::CircleEntity>(entity) });

        return entities_.at(entity.get_id());
    }
    std::shared_ptr<game::Entity> EntitiesStorage::add_entity(game::PolygonEntity entity)
    {
        entities_.insert({ entity.get_id(), std::make_shared<game::PolygonEntity>(entity) });

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
} // namespace game
