#pragma once
#include <GameEngine/PhysicsEngine/Fixture.h>


namespace physics
{
	template <typename T>
	struct Contact
	{
		std::shared_ptr<T> contact_1;
		std::shared_ptr<T> contact_2;
	};

	template <typename T>
	class ContactsManager
	{
	public:
		ContactsManager();


		void add_pair();
	private:
		std::vector<Contact<T>> contacts;
	};

} // namespace physics
