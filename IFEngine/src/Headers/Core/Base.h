#pragma once

namespace IronFang
{

	template<typename T>
	using uniqueP = std::unique_ptr<T>;

	template<typename T>
	using sharedP = std::shared_ptr<T>;

	template<typename T>
	using weakP = std::weak_ptr<T>;


	void InitializeCore();

	void ShutdownCore();

}