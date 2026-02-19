#pragma once
#include <vector>
#include "Base.h"
#include <list>

/// <summary>
/// フレームワークを参考にし作成した
/// </summary>
class ObjectManager {
private:
	std::vector<Base*> baseVector;

	ObjectManager() {}
	~ObjectManager() {}
public:
	static ObjectManager& GetInstance() {
		static ObjectManager manager;
		return manager;
	}

	void AddObject(Base* base) {
		baseVector.push_back(base);
	}

	void RemoveObject(Base* base) {
		base->isAlive_ = false;
		for (auto it = baseVector.begin(); it != baseVector.end(); ) {
			if ((*it)->IsAlive()) {
				it++;
			}
			else {
				delete* it; // メモリ解放
				it = baseVector.erase(it); // イテレータを更新
			}
		}
	}

	void UpdateObject() {
		for (int n = 0; n < baseVector.size(); n++) {
			auto& obj = baseVector[n];
			if (obj == nullptr) continue;
			if (!obj->IsAlive()) continue;
			obj->Update();
		}
	}

	void DrawObject() {
		for (int n = 0; n < baseVector.size(); n++) {
			auto& obj = baseVector.at(n);
			if (obj == nullptr) continue;
			if (!obj->IsAlive()) continue;
			obj->Draw();
		}
	}

	template<class C> C* GetGameObject() {
		for (Base* obj : baseVector) {
			if (obj == nullptr) continue;
			C* instance = dynamic_cast<C*>(obj);
			if (instance != nullptr) {
				return instance;
			}
		}
		return nullptr;
	}

	template<class C> std::vector<C*> GetGameObjects() {
		std::vector<C*> base;
		for (Base* obj : baseVector) {
			if (obj == nullptr) continue;
			C* instance = dynamic_cast<C*>(obj);

			if (instance != nullptr) {
				base.push_back(instance);
			}
		}
		return base;
	}

	int GetAllObjectSize() {
		return baseVector.size();
	}
};

