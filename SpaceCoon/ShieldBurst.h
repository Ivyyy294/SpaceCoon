#pragma once
#include <GameObject.h>

namespace LarasEngine
{
	class ShieldBurst :
		public LarasEngine::GameObject
	{
	public:
		ShieldBurst ();
		ShieldBurst (GameObject* p);

		virtual void Update () override;
		virtual void Draw (QPainter* painter) override;
		virtual void HandleCrash (GameObject* obj) override;

		static GameObject* CreateMethod () { return new ShieldBurst; };

		void SetActive ();
		inline bool GetActive () const { return active; };
		inline uint GetCost () const { return cost; }
	protected:
		void ReadJson (const QJsonObject& json) override;
	private:
		uint cost{ 0 };
		double lifeTime{ 0 };
		bool active{ false };
		GameObject* parent{nullptr};
	};
}


