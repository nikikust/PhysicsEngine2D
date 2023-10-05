#include <GameEngine/Game/Entities/EntitiesStorage.h>


namespace game
{
    EntitiesStorage::EntitiesStorage()
    {
    }


    void EntitiesStorage::add_entity(const std::shared_ptr<Entity>& entity)
    {
        entities_.insert({ entity->get_id(), entity });
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
