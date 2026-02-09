#include "ExplosionEffect.h"
#include <DxLib.h>
#include "Math2D.h"

namespace {
	const Vector2D PARTICLE_OFFSET = { 0.0f, 0.0f };
	const Vector2D PARTICLE_VELCITY = { 0.0f, 0.0f };
	const float PARTICLE_SPEED[3] = {50.0f, 100.0f, 150.0f};
	const int PARTICLE_LIFE = 3.0f;
	const int PARTICLE_RADIUS = 1.5f;
	const int PARTICLE_SIZE = 20;
	const float PARTICLE_DECAY = 0.95f; //å∏êäó¶
	int RGB_COLOR[3] = { 255, 255, 255 };
}

ExplosionEffect::ExplosionEffect(Vector2D pos, int particleCount)
	: Base(pos, {0.0f, 0.0f}, GetColor(255, 255, 255)) {
	particles_.clear();
	particles_.resize(particleCount);
	isFinished_ = false;
	Particle particle;
	particle.offset_ = PARTICLE_OFFSET;
	particle.velocity = PARTICLE_VELCITY;
	particle.life = PARTICLE_LIFE; //éıñΩ3ïb
	particle.radius = PARTICLE_RADIUS; //îºåa5

	//í«â¡Ç∑ÇÈ
	//particles_[0] = p;
	for (int n = 0; n < PARTICLE_SIZE; n++) {
		int random = (float)GetRand(360) * (Math2D::PI / 180.0f);
		Vector2D direction = Math2D::FromAngle((float)random);
		particle.velocity = Math2D::Mul(direction, PARTICLE_SPEED[GetRand(2)]);

		particles_.push_back(particle);
	}

}

void ExplosionEffect::Update()
{
	float dt = GetDeltaTime();
	bool allDead = true;

	for (auto& particle : particles_) {
		if (particle.life > 0.0f) {
			allDead = false;
			particle.offset_ = Math2D::Add(particle.offset_, Math2D::Mul(particle.velocity, dt)); // offset + (vel*dt);
			particle.velocity = Math2D::Mul(particle.velocity, PARTICLE_DECAY);
			particle.life -= dt;
		}
		if (particle.life < 0.0f) {
			particle.life = 0.0f;
		}
	}

	if (allDead) {
		isFinished_ = true;
	}
}

void ExplosionEffect::Draw() {
	if (isFinished_) return;

	for (auto& particle : particles_) {
		if (particle.life > 0.0f) {
			Vector2D drawPos = Math2D::Add(GetPos(), particle.offset_);
			Vector2D screenPos = Math2D::World2Screen(drawPos);
			//DrawCircle((int) screenPos.x, (int) screenPos.y, particle.radius, GetColor(255, 0, 0));
			
			DrawCircleAA((int)screenPos.x, (int)screenPos.y, particle.radius, 60, GetColor(RGB_COLOR[0], RGB_COLOR[1], RGB_COLOR[2]));
			RGB_COLOR[0]--;
			RGB_COLOR[1]--;
			RGB_COLOR[2]--;
		}
	}
}
