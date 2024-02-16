//#include <stdlib.h>
#include "coin_spawner.h"

void update_coin_spawner(waddle* waddle) {
	for (int entity_i = 0; entity_i < waddle->entity_count; entity_i++) {
		for (int comp_i = 0; comp_i < waddle->entities[entity_i]->component_count; comp_i++) {
			switch (waddle->entities[entity_i]->components[comp_i]->type)
			{
				case COIN_SPAWNER: {
					coin_spawner* cs = (coin_spawner*)waddle->entities[entity_i]->components[comp_i]->data;
					cs->spawn_timer += waddle->delta_time;
					if (cs->spawn_timer >= cs->time_to_spawn) {
						// spawn coin
						// Track coins spawned
						cs->coins_spawned++;

						if (cs->coins_spawned == 8) {
							printf("Spawned 8 coins...no more");
							break;
						}

						// actually spawn coin
						entity* sprite = create_entity(waddle);
						sprite->name = "coin";
						add_component(sprite, WADDLE_TRANSFORM, &(transform) {
							{ 40.0f + (float)(rand() % 560), 40.0f + (float)(rand() % 400)},
							{ 0.0f, 0.0f },
							{ 1.0f, 1.0f }
						});
						add_component(sprite, WADDLE_SPRITE_RENDERER, &(sprite_renderer) {
							{ 128.0f, 128.0f },
							{ 0xFF, 0xFF, 0xFF, 0xFF },
								"test_assets/images/Coin.png",
								NULL
						});
					}
				} break;

				default:
					break;
			}
		}
	}
}

//entity* spawn_coin(waddle* waddle) {
//	entity* sprite = create_entity(waddle);
//	sprite->name = "coin";
//	add_component(sprite, WADDLE_TRANSFORM, &(transform) {
//		{ 40.0f + (float)(rand() % 560), 40.0f + (float)(rand() % 400)},
//		{ 0.0f, 0.0f },
//		{ 1.0f, 1.0f }
//	});
//	add_component(sprite, WADDLE_SPRITE_RENDERER, &(sprite_renderer) {
//		{ 128.0f, 128.0f },
//		{ 0xFF, 0xFF, 0xFF, 0xFF },
//		"test_assets/images/Coin.png",
//		NULL
//	});
//}