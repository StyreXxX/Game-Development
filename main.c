//FULL WORKING CODE WITH PLAYER AND BOSS WITH EVOLUTION AND STAGES

 
//boss with player(3 phases, dash, zigzag, teleport phase 3, cannot fly)


// #include "raylib.h"
// #include "raymath.h"
// #include <stdio.h>
// #include <stdbool.h>
// #include <stdlib.h>

// #define SCREEN_WIDTH 800
// #define SCREEN_HEIGHT 600
// #define GROUND_Y 500   // Ground level

// #define MAX_PROJECTILES 16

// typedef struct Projectile {
//     Vector2 position;
//     Vector2 velocity;
//     bool active;
//     float radius;
// } Projectile;

// typedef struct Boss {
//     Vector2 position;
//     int health;
//     float speed;
//     int frame;
//     float frameTime;
//     float frameCounter;
//     Texture2D skillRight;
//     Texture2D skillLeft;
//     int phase;
//     bool facingRight;

//     // Dash mechanic
//     bool isDashing;
//     float dashTimer;
//     float dashCooldown;
//     float dashSpeed;

//     // Zigzag mechanic (Phase 2 and 3)
//     float zigzagTimer;
//     float zigzagAmplitude;
//     float zigzagFrequency;

//     // Teleport mechanic (Phase 3)
//     float teleportTimer;
//     float teleportCooldown;

//     // Death animation
//     bool isDead;
//     bool deathAnimPlaying;
//     int deathFrame;
//     float deathFrameCounter;
//     float deathFrameTime;
//     bool deathFinished;
// } Boss;

// typedef struct Player {
//     Vector2 position;
//     Vector2 velocity;
//     int frame;
//     float frameCounter;
//     float frameTime;
//     Texture2D texture;
//     bool facingRight;
//     bool isOnGround;
//     int health;
//     bool alive;
// } Player;

// void UpdateBoss(Boss *boss, float delta, Vector2 playerPos) {
//     if (boss->health <= 0) {
//         boss->speed = 0;
//         boss->isDashing = false;
//         boss->isDead = true;
//         return;
//     }

//     // Phase evolution
//     if (boss->health > 5000) {
//         boss->phase = 1;
//         boss->speed = 100;
//         boss->zigzagFrequency = 2.0f; // Default, not used in phase 1
//     } else if (boss->health > 2000) {
//         boss->phase = 2;
//         boss->speed = 150;
//         boss->zigzagFrequency = 2.0f; // Slower zigzag for phase 2
//     } else {
//         boss->phase = 3;
//         boss->speed = 200;
//         boss->zigzagFrequency = 3.0f; // Faster zigzag for phase 3
//     }

//     float bossWidth = (boss->skillRight.width / 6) * 1.8f;
//     float margin = 50.0f;
//     float leftBound = margin;
//     float rightBound = SCREEN_WIDTH - bossWidth - margin;

//     // Update timers
//     boss->dashTimer += delta;
//     boss->zigzagTimer += delta;
//     boss->teleportTimer += delta;

//     // Dash ability (Phase 3)
//     if (boss->phase == 3 && !boss->isDashing) {
//         if (boss->dashTimer >= boss->dashCooldown) {
//             boss->isDashing = true;
//             boss->dashTimer = 0;
//             boss->facingRight = (playerPos.x > boss->position.x);
//         }
//     }

//     // Teleport ability (Phase 3)
//     if (boss->phase == 3 && boss->teleportTimer >= boss->teleportCooldown) {
//         boss->position.x = leftBound + (float)(rand() % (int)(rightBound - leftBound));
//         boss->teleportTimer = 0.0f;
//         boss->facingRight = (playerPos.x > boss->position.x);
//     }

//     if (boss->isDashing) {
//         float dashDir = boss->facingRight ? 1 : -1;
//         boss->position.x += dashDir * boss->dashSpeed * delta;
//         if (boss->dashTimer > 0.5f) {
//             boss->isDashing = false;
//             boss->dashTimer = 0;
//         }
//     } else if (boss->phase == 2 || boss->phase == 3) {
//         // Zigzag movement in Phase 2 and 3
//         float dir = boss->facingRight ? 1 : -1;
//         boss->position.x += dir * boss->speed * delta;
//         float zigzagOffset = boss->zigzagAmplitude * sinf(boss->zigzagTimer * boss->zigzagFrequency);
//         boss->position.x += zigzagOffset;

//         if (boss->position.x < leftBound) {
//             boss->facingRight = true;
//             boss->position.x = leftBound;
//         }
//         if (boss->position.x > rightBound) {
//             boss->facingRight = false;
//             boss->position.x = rightBound;
//         }
//     } else if (boss->phase == 1) {
//         // Normal movement in Phase 1
//         float dir = boss->facingRight ? 1 : -1;
//         boss->position.x += dir * boss->speed * delta;

//         if (boss->position.x < leftBound) boss->facingRight = true;
//         if (boss->position.x > rightBound) boss->facingRight = false;
//     }

//     // Clamp position to screen bounds
//     boss->position.x = Clamp(boss->position.x, 0.0f, SCREEN_WIDTH - bossWidth);

//     // Frame animation
//     boss->frameCounter += delta;
//     if (boss->frameCounter >= boss->frameTime) {
//         boss->frameCounter = 0;
//         boss->frame++;
//         if (boss->frame >= 6) boss->frame = 0;
//     }
// }

// void DrawBoss(Boss *boss, Texture2D deathTex) {
//     float scale = 1.8f;

//     if (boss->isDead) {
//         if (!boss->deathAnimPlaying && !boss->deathFinished) {
//             boss->deathAnimPlaying = true;
//             boss->deathFrame = 0;
//             boss->deathFrameCounter = 0;
//         }

//         if (boss->deathAnimPlaying && !boss->deathFinished) {
//             int cols = 10;
//             int rows = 2;
//             int frameWidth = deathTex.width / cols;
//             int frameHeight = deathTex.height / rows;

//             int currentRow = boss->deathFrame / cols;
//             int currentCol = boss->deathFrame % cols;

//             Rectangle source = {
//                 currentCol * frameWidth,
//                 currentRow * frameHeight,
//                 frameWidth,
//                 frameHeight
//             };
//             Rectangle dest = {
//                 boss->position.x,
//                 boss->position.y,
//                 frameWidth * scale,
//                 frameHeight * scale
//             };

//             DrawTexturePro(deathTex, source, dest, (Vector2){0,0}, 0, WHITE);

//             boss->deathFrameCounter += GetFrameTime();
//             if (boss->deathFrameCounter >= boss->deathFrameTime) {
//                 boss->deathFrameCounter = 0;
//                 boss->deathFrame++;
//                 if (boss->deathFrame >= cols * rows) {
//                     boss->deathAnimPlaying = false;
//                     boss->deathFinished = true;
//                 }
//             }
//         }
//         return;
//     }

//     int frameWidth = boss->skillRight.width / 6;
//     int frameHeight = boss->skillRight.height;
//     Rectangle source = { boss->frame * frameWidth, 0, frameWidth, frameHeight };
//     Rectangle dest = { boss->position.x, boss->position.y, frameWidth * scale, frameHeight * scale };

//     Texture2D current = boss->facingRight ? boss->skillRight : boss->skillLeft;
//     DrawTexturePro(current, source, dest, (Vector2){0,0}, 0, WHITE);
// }

// void UpdatePlayer(Player *player, float delta) {
//     // If player dead, prevent movement
//     if (!player->alive) return;

//     float speed = 200.0f;
//     float gravity = 600.0f;
//     float jumpForce = -600.0f;

//     // Horizontal movement
//     if (IsKeyDown(KEY_A)) {
//         player->position.x -= speed * delta;
//         player->facingRight = false;
//     }
//     if (IsKeyDown(KEY_D)) {
//         player->position.x += speed * delta;
//         player->facingRight = true;
//     }

//     // Clamp player position to screen bounds
//     float playerWidth = (player->texture.width / 6) * 0.4f;
//     player->position.x = Clamp(player->position.x, 0.0f, SCREEN_WIDTH - playerWidth);

//     // Jump
//     if (IsKeyPressed(KEY_W) && player->isOnGround) {
//         player->velocity.y = jumpForce;
//         player->isOnGround = false;
//     }

//     // Apply gravity
//     player->velocity.y += gravity * delta;
//     player->position.y += player->velocity.y * delta;

//     // Ground collision
//     int frameHeight = player->texture.height;
//     float scale = 0.4f;
//     float playerHeight = frameHeight * scale;

//     if (player->position.y + playerHeight >= GROUND_Y) {
//         player->position.y = GROUND_Y - playerHeight;
//         player->velocity.y = 0;
//         player->isOnGround = true;
//     }

//     // Frame animation
//     player->frameCounter += delta;
//     if (player->frameCounter >= player->frameTime) {
//         player->frameCounter = 0;
//         player->frame++;
//         if (player->frame >= 6) player->frame = 0;
//     }
// }

// void DrawPlayer(Player *player) {
//     int frameWidth = player->texture.width / 6;
//     int frameHeight = player->texture.height;
//     float scale = 0.4f;

//     Rectangle source = { player->frame * frameWidth, 0, frameWidth, frameHeight };
//     if (!player->facingRight) source.width *= -1;

//     Rectangle dest = { player->position.x, player->position.y, frameWidth * scale, frameHeight * scale };
//     DrawTexturePro(player->texture, source, dest, (Vector2){0,0}, 0, WHITE);
// }

// int main(void) {
//     InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Boss + Scarfy");
//     SetTargetFPS(60);

//     // Initialize random seed for teleportation
//     SetRandomSeed((unsigned int)GetTime());

//     // Boss setup
//     Boss boss = {0};
//     boss.position = (Vector2){500, GROUND_Y - 180};
//     boss.health = 10000;
//     boss.frame = 0;
//     boss.frameTime = 0.15f;
//     boss.frameCounter = 0;
//     boss.dashCooldown = 3.0f;
//     boss.dashSpeed = 500.0f;
//     boss.isDashing = false;
//     boss.isDead = false;
//     boss.deathAnimPlaying = false;
//     boss.deathFrame = 0;
//     boss.deathFrameCounter = 0;
//     boss.deathFrameTime = 0.12f;
//     boss.deathFinished = false;
//     boss.facingRight = false;
//     boss.zigzagTimer = 0.0f;
//     boss.zigzagAmplitude = 50.0f;
//     boss.zigzagFrequency = 2.0f;
//     boss.teleportTimer = 0.0f;
//     boss.teleportCooldown = 4.0f;

//     Texture2D skill1 = LoadTexture("skill1.png");
//     Texture2D skill2 = LoadTexture("skill2.png");
//     Texture2D skill3 = LoadTexture("skill3.png");
//     Texture2D skill4 = LoadTexture("skill4.png");
//     Texture2D skill5 = LoadTexture("skill5.png");
//     Texture2D skill6 = LoadTexture("skill6.png");
//     Texture2D skill7 = LoadTexture("skill7.png"); // death sheet

//     boss.skillRight = skill1;
//     boss.skillLeft = skill2;

//     // Player setup
//     Player player = {0};
//     player.texture = LoadTexture("scarfy.png");
//     // place player so sprite bottom touches ground
//     float playerScale = 0.4f;
//     player.position = (Vector2){200, GROUND_Y - player.texture.height * playerScale};
//     player.velocity = (Vector2){0, 0};
//     player.frame = 0;
//     player.frameTime = 0.15f;
//     player.frameCounter = 0;
//     player.facingRight = true;
//     player.isOnGround = true;
//     player.health = 2000;
//     player.alive = true;

//     // Projectiles
//     Projectile projectiles[MAX_PROJECTILES] = {0};
//     for (int i = 0; i < MAX_PROJECTILES; i++) {
//         projectiles[i].active = false;
//         projectiles[i].radius = 6.0f;
//     }

//     // Proximity damage control
//     float proximityCooldown = 0.6f; // seconds between each proximity damage instance
//     float proximityTimer = 0.0f;
//     int proximityDamage = 200;

//     // Projectile settings
//     float projSpeed = 400.0f; // Slightly increased projectile speed
//     float shootCooldown = 0.5f; // Cooldown between shots
//     float shootTimer = 0.0f; // Timer to track shooting cooldown

//     while (!WindowShouldClose()) {
//         float delta = GetFrameTime();
//         shootTimer += delta; // Update shooting timer

//         // SHOOT: press 1 to spawn projectile with cooldown
//         if (IsKeyPressed(KEY_ONE) && shootTimer >= shootCooldown) {
//             // find free projectile
//             for (int i = 0; i < MAX_PROJECTILES; i++) {
//                 if (!projectiles[i].active) {
//                     projectiles[i].active = true;
//                     // spawn near player's center
//                     projectiles[i].position.x = player.position.x + (player.facingRight ? 40 : -10);
//                     projectiles[i].position.y = player.position.y + player.texture.height * 0.25f;
//                     projectiles[i].velocity.x = (player.facingRight ? 1 : -1) * projSpeed;
//                     projectiles[i].velocity.y = 0;
//                     shootTimer = 0.0f; // Reset shoot timer
//                     break;
//                 }
//             }
//         }

//         // Update projectiles
//         for (int i = 0; i < MAX_PROJECTILES; i++) {
//             if (!projectiles[i].active) continue;
//             projectiles[i].position.x += projectiles[i].velocity.x * delta;
//             projectiles[i].position.y += projectiles[i].velocity.y * delta;

//             // deactivate if offscreen
//             if (projectiles[i].position.x < -50 || projectiles[i].position.x > SCREEN_WIDTH + 50) {
//                 projectiles[i].active = false;
//             }
//         }

//         // Update player (movement disabled if dead)
//         UpdatePlayer(&player, delta);

//         // Update boss AI if not dead
//         if (!boss.isDead) {
//             if (boss.phase == 1) {
//                 boss.skillRight = skill1;
//                 boss.skillLeft = skill2;
//             } else if (boss.phase == 2) {
//                 boss.skillRight = skill3;
//                 boss.skillLeft = skill4;
//             } else {
//                 boss.skillRight = skill5;
//                 boss.skillLeft = skill6;
//             }
//             UpdateBoss(&boss, delta, player.position);
//         }

//         // Projectile - Boss collisions
//         for (int i = 0; i < MAX_PROJECTILES; i++) {
//             if (!projectiles[i].active) continue;

//             // Treat boss as rectangle around its drawn sprite
//             float bossW = boss.skillRight.width / 6 * 1.8f;
//             float bossH = boss.skillRight.height * 1.8f;
//             Rectangle bossRect = { boss.position.x, boss.position.y, bossW, bossH };

//             // projectile as circle / small rectangle
//             Rectangle projRect = { projectiles[i].position.x - projectiles[i].radius,
//                                    projectiles[i].position.y - projectiles[i].radius,
//                                    projectiles[i].radius * 2, projectiles[i].radius * 2 };

//             if (CheckCollisionRecs(bossRect, projRect)) {
//                 // hit!
//                 projectiles[i].active = false;
//                 if (!boss.isDead) {
//                     boss.health -= 300; // deduct 300 hp per hit
//                     if (boss.health < 0) boss.health = 0;
//                 }
//             }
//         }

//         // Player - Boss collision damage
//         proximityTimer += delta;

//         if (proximityTimer >= proximityCooldown && !boss.isDead && player.alive) {
//             // Define player rect
//             float pScale = 0.4f;
//             float pW = (player.texture.width / 6) * pScale;
//             float pH = player.texture.height * pScale;
//             Rectangle playerRect = { player.position.x, player.position.y, pW, pH };

//             // Define boss rect
//             float bScale = 1.8f;
//             float bW = (boss.skillRight.width / 6) * bScale;
//             float bH = boss.skillRight.height * bScale;
//             Rectangle bossRect = { boss.position.x, boss.position.y, bW, bH };

//             // Check if player is above the boss to avoid damage when jumping over
//             bool isAboveBoss = player.position.y + pH < boss.position.y;

//             if (CheckCollisionRecs(playerRect, bossRect) && !isAboveBoss) {
//                 player.health -= proximityDamage;
//                 if (player.health < 0) player.health = 0;
//                 proximityTimer = 0.0f;

//                 if (player.health <= 0) {
//                     player.alive = false;
//                     // Stop movement and maybe play death anim - here we simply stop movement
//                 }
//             }
//         }

//         BeginDrawing();
//         ClearBackground(RAYWHITE);

//         // Draw ground
//         DrawRectangle(0, GROUND_Y, SCREEN_WIDTH, SCREEN_HEIGHT - GROUND_Y, DARKGREEN);

//         // Draw player and boss
//         DrawPlayer(&player);
//         DrawBoss(&boss, skill7);

//         // Draw active projectiles
//         for (int i = 0; i < MAX_PROJECTILES; i++) {
//             if (!projectiles[i].active) continue;
//             DrawCircleV(projectiles[i].position, projectiles[i].radius, BLACK);
//         }

//         // Draw Boss health bar (top)
//         int barWidth = 700;
//         int barHeight = 26;
//         int barX = (SCREEN_WIDTH - barWidth) / 2;
//         int barY = 18;

//         // Border
//         DrawRectangleLines(barX - 2, barY - 2, barWidth + 4, barHeight + 4, BLACK);

//         // Filled background (empty)
//         DrawRectangle(barX, barY, barWidth, barHeight, LIGHTGRAY);

//         // Fill based on boss.health
//         float bossHealthRatio = (float)boss.health / 10000.0f;
//         if (bossHealthRatio < 0) bossHealthRatio = 0;
//         DrawRectangle(barX, barY, (int)(barWidth * bossHealthRatio), barHeight, RED);

//         // HP text (black)
//         char hpText[64];
//         sprintf(hpText, "BOSS HP: %d", boss.health);
//         int fontSize = 20;
//         Vector2 txtSize = MeasureTextEx(GetFontDefault(), hpText, fontSize, 0);
//         DrawText(hpText, barX + (barWidth - (int)txtSize.x) / 2, barY + (barHeight - fontSize) / 2, fontSize, BLACK);

//         // Draw Scarfy (player) health bar at bottom
//         int pBarWidth = 300;
//         int pBarHeight = 20;
//         int pBarX = 20;
//         int pBarY = SCREEN_HEIGHT - pBarHeight - 20;

//         DrawRectangleLines(pBarX - 2, pBarY - 2, pBarWidth + 4, pBarHeight + 4, BLACK);
//         DrawRectangle(pBarX, pBarY, pBarWidth, pBarHeight, LIGHTGRAY);

//         float playerHealthRatio = (float)player.health / 2000.0f;
//         if (playerHealthRatio < 0) playerHealthRatio = 0;
//         DrawRectangle(pBarX, pBarY, (int)(pBarWidth * playerHealthRatio), pBarHeight, RED);

//         char pText[64];
//         sprintf(pText, "SCARFY HP: %d", player.health);
//         DrawText(pText, pBarX + 6, pBarY - 22, 18, BLACK);

//         EndDrawing();
//     }

//     // Unload textures
//     UnloadTexture(skill1);
//     UnloadTexture(skill2);
//     UnloadTexture(skill3);
//     UnloadTexture(skill4);
//     UnloadTexture(skill5);
//     UnloadTexture(skill6);
//     UnloadTexture(skill7);
//     UnloadTexture(player.texture);

//     CloseWindow();
//     return 0;
// }





//boss without player(cannot fly here, but has dash, zigzag and teleport in phase 3)





// #include "raylib.h"
// #include "raymath.h"
// #include <stdio.h>
// #include <stdbool.h>
// #include <stdlib.h>

// #define SCREEN_WIDTH 800
// #define SCREEN_HEIGHT 600
// #define GROUND_Y 500   // Ground level

// typedef struct Boss {
//     Vector2 position;
//     int health;
//     float speed;
//     int frame;
//     float frameTime;
//     float frameCounter;
//     Texture2D skillRight;
//     Texture2D skillLeft;
//     int phase;
//     bool facingRight;

//     // Dash mechanic
//     bool isDashing;
//     float dashTimer;
//     float dashCooldown;
//     float dashSpeed;

//     // Zigzag mechanic (Phase 2 and 3)
//     float zigzagTimer;
//     float zigzagAmplitude;
//     float zigzagFrequency;

//     // Teleport mechanic (Phase 3)
//     float teleportTimer;
//     float teleportCooldown;

//     // Death animation
//     bool isDead;
//     bool deathAnimPlaying;
//     int deathFrame;
//     float deathFrameCounter;
//     float deathFrameTime;
//     bool deathFinished;
// } Boss;

// void UpdateBoss(Boss *boss, float delta) {
//     if (boss->health <= 0) {
//         boss->speed = 0;
//         boss->isDashing = false;
//         boss->isDead = true;
//         return;
//     }

//     // Phase evolution
//     if (boss->health > 5000) {
//         boss->phase = 1;
//         boss->speed = 100;
//         boss->zigzagFrequency = 2.0f; // Default, not used in phase 1
//     } else if (boss->health > 2000) {
//         boss->phase = 2;
//         boss->speed = 150;
//         boss->zigzagFrequency = 2.0f; // Slower zigzag for phase 2
//     } else {
//         boss->phase = 3;
//         boss->speed = 200;
//         boss->zigzagFrequency = 3.0f; // Faster zigzag for phase 3
//     }

//     float bossWidth = (boss->skillRight.width / 6) * 1.8f;
//     float margin = 50.0f;
//     float leftBound = margin;
//     float rightBound = SCREEN_WIDTH - bossWidth - margin;

//     // Update timers
//     boss->dashTimer += delta;
//     boss->zigzagTimer += delta;
//     boss->teleportTimer += delta;

//     // Dash ability (Phase 3)
//     if (boss->phase == 3 && !boss->isDashing) {
//         if (boss->dashTimer >= boss->dashCooldown) {
//             boss->isDashing = true;
//             boss->dashTimer = 0;
//             boss->facingRight = (rand() % 2) == 0; // Randomly choose direction
//         }
//     }

//     // Teleport ability (Phase 3)
//     if (boss->phase == 3 && boss->teleportTimer >= boss->teleportCooldown) {
//         boss->position.x = leftBound + (float)(rand() % (int)(rightBound - leftBound));
//         boss->teleportTimer = 0.0f;
//         boss->facingRight = (rand() % 2) == 0; // Randomly choose direction
//     }

//     if (boss->isDashing) {
//         float dashDir = boss->facingRight ? 1 : -1;
//         boss->position.x += dashDir * boss->dashSpeed * delta;
//         if (boss->dashTimer > 0.5f) {
//             boss->isDashing = false;
//             boss->dashTimer = 0;
//         }
//     } else if (boss->phase == 2 || boss->phase == 3) {
//         // Zigzag movement in Phase 2 and 3
//         float dir = boss->facingRight ? 1 : -1;
//         boss->position.x += dir * boss->speed * delta;
//         float zigzagOffset = boss->zigzagAmplitude * sinf(boss->zigzagTimer * boss->zigzagFrequency);
//         boss->position.x += zigzagOffset;

//         if (boss->position.x < leftBound) {
//             boss->facingRight = true;
//             boss->position.x = leftBound;
//         }
//         if (boss->position.x > rightBound) {
//             boss->facingRight = false;
//             boss->position.x = rightBound;
//         }
//     } else if (boss->phase == 1) {
//         // Normal movement in Phase 1
//         float dir = boss->facingRight ? 1 : -1;
//         boss->position.x += dir * boss->speed * delta;

//         if (boss->position.x < leftBound) boss->facingRight = true;
//         if (boss->position.x > rightBound) boss->facingRight = false;
//     }

//     // Clamp position to screen bounds
//     boss->position.x = Clamp(boss->position.x, 0.0f, SCREEN_WIDTH - bossWidth);

//     // Frame animation
//     boss->frameCounter += delta;
//     if (boss->frameCounter >= boss->frameTime) {
//         boss->frameCounter = 0;
//         boss->frame++;
//         if (boss->frame >= 6) boss->frame = 0;
//     }
// }

// void DrawBoss(Boss *boss, Texture2D deathTex) {
//     float scale = 1.8f;

//     if (boss->isDead) {
//         if (!boss->deathAnimPlaying && !boss->deathFinished) {
//             boss->deathAnimPlaying = true;
//             boss->deathFrame = 0;
//             boss->deathFrameCounter = 0;
//         }

//         if (boss->deathAnimPlaying && !boss->deathFinished) {
//             int cols = 10;
//             int rows = 2;
//             int frameWidth = deathTex.width / cols;
//             int frameHeight = deathTex.height / rows;

//             int currentRow = boss->deathFrame / cols;
//             int currentCol = boss->deathFrame % cols;

//             Rectangle source = {
//                 currentCol * frameWidth,
//                 currentRow * frameHeight,
//                 frameWidth,
//                 frameHeight
//             };
//             Rectangle dest = {
//                 boss->position.x,
//                 boss->position.y,
//                 frameWidth * scale,
//                 frameHeight * scale
//             };

//             DrawTexturePro(deathTex, source, dest, (Vector2){0,0}, 0, WHITE);

//             boss->deathFrameCounter += GetFrameTime();
//             if (boss->deathFrameCounter >= boss->deathFrameTime) {
//                 boss->deathFrameCounter = 0;
//                 boss->deathFrame++;
//                 if (boss->deathFrame >= cols * rows) {
//                     boss->deathAnimPlaying = false;
//                     boss->deathFinished = true;
//                 }
//             }
//         }
//         return;
//     }

//     int frameWidth = boss->skillRight.width / 6;
//     int frameHeight = boss->skillRight.height;
//     Rectangle source = { boss->frame * frameWidth, 0, frameWidth, frameHeight };
//     Rectangle dest = { boss->position.x, boss->position.y, frameWidth * scale, frameHeight * scale };

//     Texture2D current = boss->facingRight ? boss->skillRight : boss->skillLeft;
//     DrawTexturePro(current, source, dest, (Vector2){0,0}, 0, WHITE);
// }

// int main(void) {
//     InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Boss");
//     SetTargetFPS(60);

//     // Initialize random seed for teleportation and direction
//     SetRandomSeed((unsigned int)GetTime());

//     // Boss setup
//     Boss boss = {0};
//     boss.position = (Vector2){500, GROUND_Y - 180};
//     boss.health = 10000;
//     boss.frame = 0;
//     boss.frameTime = 0.15f;
//     boss.frameCounter = 0;
//     boss.dashCooldown = 3.0f;
//     boss.dashSpeed = 500.0f;
//     boss.isDashing = false;
//     boss.isDead = false;
//     boss.deathAnimPlaying = false;
//     boss.deathFrame = 0;
//     boss.deathFrameCounter = 0;
//     boss.deathFrameTime = 0.12f;
//     boss.deathFinished = false;
//     boss.facingRight = false;
//     boss.zigzagTimer = 0.0f;
//     boss.zigzagAmplitude = 50.0f;
//     boss.zigzagFrequency = 2.0f;
//     boss.teleportTimer = 0.0f;
//     boss.teleportCooldown = 4.0f;

//     Texture2D skill1 = LoadTexture("skill1.png");
//     Texture2D skill2 = LoadTexture("skill2.png");
//     Texture2D skill3 = LoadTexture("skill3.png");
//     Texture2D skill4 = LoadTexture("skill4.png");
//     Texture2D skill5 = LoadTexture("skill5.png");
//     Texture2D skill6 = LoadTexture("skill6.png");
//     Texture2D skill7 = LoadTexture("skill7.png"); // death sheet

//     boss.skillRight = skill1;
//     boss.skillLeft = skill2;

//     while (!WindowShouldClose()) {
//         float delta = GetFrameTime();

//         // Update boss AI if not dead
//         if (!boss.isDead) {
//             if (boss.phase == 1) {
//                 boss.skillRight = skill1;
//                 boss.skillLeft = skill2;
//             } else if (boss.phase == 2) {
//                 boss.skillRight = skill3;
//                 boss.skillLeft = skill4;
//             } else {
//                 boss.skillRight = skill5;
//                 boss.skillLeft = skill6;
//             }
//             UpdateBoss(&boss, delta);
//         }

//         BeginDrawing();
//         ClearBackground(RAYWHITE);

//         // Draw ground
//         DrawRectangle(0, GROUND_Y, SCREEN_WIDTH, SCREEN_HEIGHT - GROUND_Y, DARKGREEN);

//         // Draw boss
//         DrawBoss(&boss, skill7);

//         // Draw Boss health bar (top)
//         int barWidth = 700;
//         int barHeight = 26;
//         int barX = (SCREEN_WIDTH - barWidth) / 2;
//         int barY = 18;

//         // Border
//         DrawRectangleLines(barX - 2, barY - 2, barWidth + 4, barHeight + 4, BLACK);

//         // Filled background (empty)
//         DrawRectangle(barX, barY, barWidth, barHeight, LIGHTGRAY);

//         // Fill based on boss.health
//         float bossHealthRatio = (float)boss.health / 10000.0f;
//         if (bossHealthRatio < 0) bossHealthRatio = 0;
//         DrawRectangle(barX, barY, (int)(barWidth * bossHealthRatio), barHeight, RED);

//         // HP text (black)
//         char hpText[64];
//         sprintf(hpText, "BOSS HP: %d", boss.health);
//         int fontSize = 20;
//         Vector2 txtSize = MeasureTextEx(GetFontDefault(), hpText, fontSize, 0);
//         DrawText(hpText, barX + (barWidth - (int)txtSize.x) / 2, barY + (barHeight - fontSize) / 2, fontSize, BLACK);

//         EndDrawing();
//     }

//     // Unload textures
//     UnloadTexture(skill1);
//     UnloadTexture(skill2);
//     UnloadTexture(skill3);
//     UnloadTexture(skill4);
//     UnloadTexture(skill5);
//     UnloadTexture(skill6);
//     UnloadTexture(skill7);

//     CloseWindow();
//     return 0;
// }


















//boss with more powers(can fly, dash, teleport, zigzag and fly)











// #include "raylib.h"
// #include "raymath.h"
// #include <math.h>
// #include <stdio.h>
// #include <stdbool.h>
// #include <stdlib.h>

// #define SCREEN_WIDTH 800
// #define SCREEN_HEIGHT 600
// #define GROUND_Y 500   // Ground level

// #define MAX_PROJECTILES 16

// typedef struct Projectile {
//     Vector2 position;
//     Vector2 velocity;
//     bool active;
//     float radius;
// } Projectile;

// typedef struct Boss {
//     Vector2 position;
//     int health;
//     float speed;
//     int frame;
//     float frameTime;
//     float frameCounter;
//     Texture2D skillRight;
//     Texture2D skillLeft;
//     int phase;
//     bool facingRight;

//     // Dash mechanic
//     bool isDashing;
//     float dashTimer;
//     float dashCooldown;
//     float dashSpeed;

//     // Zigzag mechanic (Phase 2 and 3)
//     float zigzagTimer;
//     float zigzagAmplitude;
//     float zigzagFrequency;

//     // Teleport mechanic (Phase 2 and 3)
//     float teleportTimer;
//     float teleportCooldown;

//     // Flying mechanic (Phase 3)
//     bool isFlying;

//     // Death animation
//     bool isDead;
//     bool deathAnimPlaying;
//     int deathFrame;
//     float deathFrameCounter;
//     float deathFrameTime;
//     bool deathFinished;
// } Boss;

// typedef struct Player {
//     Vector2 position;
//     Vector2 velocity;
//     int frame;
//     float frameCounter;
//     float frameTime;
//     Texture2D texture;
//     bool facingRight;
//     bool isOnGround;
//     int health;
//     bool alive;
// } Player;

// void UpdateBoss(Boss *boss, float delta, Player *player) {
//     if (boss->health <= 0) {
//         boss->speed = 0;
//         boss->isDashing = false;
//         boss->isDead = true;
//         return;
//     }

//     // Phase evolution
//     if (boss->health > 5000) {
//         boss->phase = 1;
//         boss->speed = 100;
//         boss->zigzagFrequency = 2.0f; // Default, not used in phase 1
//         boss->isFlying = false;
//     } else if (boss->health > 2000) {
//         boss->phase = 2;
//         boss->speed = 150;
//         boss->zigzagFrequency = 2.0f; // Zigzag for phase 2
//         boss->isFlying = false;
//     } else {
//         boss->phase = 3;
//         boss->speed = 200;
//         boss->zigzagFrequency = 2.0f; // Zigzag for phase 3
//         boss->isFlying = true;
//     }

//     float bossWidth = (boss->skillRight.width / 6) * 1.8f;
//     float bossHeight = (boss->skillRight.height) * 1.8f;
//     float margin = 50.0f;
//     float leftBound = margin;
//     float rightBound = SCREEN_WIDTH - bossWidth - margin;
//     float topBound = 50.0f;
//     float bottomBound = boss->isFlying ? 300.0f : GROUND_Y - bossHeight;

//     // Update timers
//     boss->dashTimer += delta;
//     boss->zigzagTimer += delta;
//     boss->teleportTimer += delta;

//     // Phase 3: Flying with zigzag, dash, and random teleport to Scarfy
//     if (boss->phase == 3) {
//         // Teleport to Scarfy randomly
//         if (boss->teleportTimer >= boss->teleportCooldown) {
//             if (rand() % 100 < 20) { // 20% chance to teleport to Scarfy
//                 boss->position.x = player->position.x;
//                 boss->position.y = player->isOnGround ? GROUND_Y - bossHeight : player->position.y;
//             }
//             boss->teleportTimer = 0.0f;
//             boss->facingRight = (player->position.x > boss->position.x);
//         }

//         // Dash ability
//         if (!boss->isDashing && boss->dashTimer >= boss->dashCooldown) {
//             boss->isDashing = true;
//             boss->dashTimer = 0;
//             boss->facingRight = (player->position.x > boss->position.x);
//         }

//         if (boss->isDashing) {
//             float dashDir = boss->facingRight ? 1 : -1;
//             boss->position.x += dashDir * boss->dashSpeed * delta;
//             if (boss->dashTimer > 0.5f) {
//                 boss->isDashing = false;
//                 boss->dashTimer = 0;
//             }
//         } else {
//             // Zigzag movement in x and y
//             float dir = boss->facingRight ? 1 : -1;
//             boss->position.x += dir * boss->speed * delta;
//             float zigzagOffsetX = boss->zigzagAmplitude * sinf(boss->zigzagTimer * boss->zigzagFrequency);
//             boss->position.x += zigzagOffsetX;
//             // Vertical oscillation for flying
//             float zigzagOffsetY = boss->zigzagAmplitude * 0.5f * sinf(boss->zigzagTimer * boss->zigzagFrequency * 0.5f);
//             boss->position.y += zigzagOffsetY;

//             if (boss->position.x < leftBound) {
//                 boss->facingRight = true;
//                 boss->position.x = leftBound;
//             }
//             if (boss->position.x > rightBound) {
//                 boss->facingRight = false;
//                 boss->position.x = rightBound;
//             }
//         }

//         // Clamp position to screen bounds
//         boss->position.x = Clamp(boss->position.x, leftBound, rightBound);
//         boss->position.y = Clamp(boss->position.y, topBound, bottomBound);
//     }
//     // Phase 2: Zigzag, dash, and teleport to Scarfy
//     else if (boss->phase == 2) {
//         // Dash ability
//         if (!boss->isDashing && boss->dashTimer >= boss->dashCooldown) {
//             boss->isDashing = true;
//             boss->dashTimer = 0;
//             boss->facingRight = (player->position.x > boss->position.x);
//         }

//         // Teleport to Scarfy
//         if (boss->teleportTimer >= boss->teleportCooldown) {
//             boss->position.x = player->position.x;
//             boss->position.y = GROUND_Y - bossHeight; // Always teleport to ground level
//             boss->teleportTimer = 0.0f;
//             boss->facingRight = (player->position.x > boss->position.x);
//         }

//         if (boss->isDashing) {
//             float dashDir = boss->facingRight ? 1 : -1;
//             boss->position.x += dashDir * boss->dashSpeed * delta;
//             if (boss->dashTimer > 0.5f) {
//                 boss->isDashing = false;
//                 boss->dashTimer = 0;
//             }
//         } else {
//             // Zigzag movement
//             float dir = boss->facingRight ? 1 : -1;
//             boss->position.x += dir * boss->speed * delta;
//             float zigzagOffset = boss->zigzagAmplitude * sinf(boss->zigzagTimer * boss->zigzagFrequency);
//             boss->position.x += zigzagOffset;

//             if (boss->position.x < leftBound) {
//                 boss->facingRight = true;
//                 boss->position.x = leftBound;
//             }
//             if (boss->position.x > rightBound) {
//                 boss->facingRight = false;
//                 boss->position.x = rightBound;
//             }
//         }

//         // Clamp position to screen bounds
//         boss->position.x = Clamp(boss->position.x, leftBound, rightBound);
//         boss->position.y = GROUND_Y - bossHeight; // Stay on ground
//     }
//     // Phase 1: Normal movement
//     else if (boss->phase == 1) {
//         float dir = boss->facingRight ? 1 : -1;
//         boss->position.x += dir * boss->speed * delta;

//         if (boss->position.x < leftBound) boss->facingRight = true;
//         if (boss->position.x > rightBound) boss->facingRight = false;

//         // Clamp position to screen bounds
//         boss->position.x = Clamp(boss->position.x, leftBound, rightBound);
//         boss->position.y = GROUND_Y - bossHeight;
//     }

//     // Frame animation
//     boss->frameCounter += delta;
//     if (boss->frameCounter >= boss->frameTime) {
//         boss->frameCounter = 0;
//         boss->frame++;
//         if (boss->frame >= 6) boss->frame = 0;
//     }
// }

// void DrawBoss(Boss *boss, Texture2D deathTex) {
//     float scale = 1.8f;

//     if (boss->isDead) {
//         if (!boss->deathAnimPlaying && !boss->deathFinished) {
//             boss->deathAnimPlaying = true;
//             boss->deathFrame = 0;
//             boss->deathFrameCounter = 0;
//         }

//         if (boss->deathAnimPlaying && !boss->deathFinished) {
//             int cols = 10;
//             int rows = 2;
//             int frameWidth = deathTex.width / cols;
//             int frameHeight = deathTex.height / rows;

//             int currentRow = boss->deathFrame / cols;
//             int currentCol = boss->deathFrame % cols;

//             Rectangle source = {
//                 currentCol * frameWidth,
//                 currentRow * frameHeight,
//                 frameWidth,
//                 frameHeight
//             };
//             Rectangle dest = {
//                 boss->position.x,
//                 boss->position.y,
//                 frameWidth * scale,
//                 frameHeight * scale
//             };

//             DrawTexturePro(deathTex, source, dest, (Vector2){0,0}, 0, WHITE);

//             boss->deathFrameCounter += GetFrameTime();
//             if (boss->deathFrameCounter >= boss->deathFrameTime) {
//                 boss->deathFrameCounter = 0;
//                 boss->deathFrame++;
//                 if (boss->deathFrame >= cols * rows) {
//                     boss->deathAnimPlaying = false;
//                     boss->deathFinished = true;
//                 }
//             }
//         }
//         return;
//     }

//     int frameWidth = boss->skillRight.width / 6;
//     int frameHeight = boss->skillRight.height;
//     Rectangle source = { boss->frame * frameWidth, 0, frameWidth, frameHeight };
//     Rectangle dest = { boss->position.x, boss->position.y, frameWidth * scale, frameHeight * scale };

//     Texture2D current = boss->facingRight ? boss->skillRight : boss->skillLeft;
//     DrawTexturePro(current, source, dest, (Vector2){0,0}, 0, WHITE);
// }

// void UpdatePlayer(Player *player, float delta) {
//     if (!player->alive) return;

//     float speed = 200.0f;
//     float gravity = 600.0f;
//     float jumpForce = -600.0f;

//     if (IsKeyDown(KEY_A)) {
//         player->position.x -= speed * delta;
//         player->facingRight = false;
//     }
//     if (IsKeyDown(KEY_D)) {
//         player->position.x += speed * delta;
//         player->facingRight = true;
//     }

//     float playerWidth = (player->texture.width / 6) * 0.4f;
//     player->position.x = Clamp(player->position.x, 0.0f, SCREEN_WIDTH - playerWidth);

//     if (IsKeyPressed(KEY_W) && player->isOnGround) {
//         player->velocity.y = jumpForce;
//         player->isOnGround = false;
//     }

//     player->velocity.y += gravity * delta;
//     player->position.y += player->velocity.y * delta;

//     int frameHeight = player->texture.height;
//     float scale = 0.4f;
//     float playerHeight = frameHeight * scale;

//     if (player->position.y + playerHeight >= GROUND_Y) {
//         player->position.y = GROUND_Y - playerHeight;
//         player->velocity.y = 0;
//         player->isOnGround = true;
//     }

//     player->frameCounter += delta;
//     if (player->frameCounter >= player->frameTime) {
//         player->frameCounter = 0;
//         player->frame++;
//         if (player->frame >= 6) player->frame = 0;
//     }
// }

// void DrawPlayer(Player *player) {
//     int frameWidth = player->texture.width / 6;
//     int frameHeight = player->texture.height;
//     float scale = 0.4f;

//     Rectangle source = { player->frame * frameWidth, 0, frameWidth, frameHeight };
//     if (!player->facingRight) source.width *= -1;

//     Rectangle dest = { player->position.x, player->position.y, frameWidth * scale, frameHeight * scale };
//     DrawTexturePro(player->texture, source, dest, (Vector2){0,0}, 0, WHITE);
// }

// int main(void) {
//     InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Boss + Scarfy");
//     SetTargetFPS(60);

//     SetRandomSeed((unsigned int)GetTime());

//     // Boss setup
//     Boss boss = {0};
//     boss.position = (Vector2){500, GROUND_Y - 180};
//     boss.health = 10000;
//     boss.frame = 0;
//     boss.frameTime = 0.15f;
//     boss.frameCounter = 0;
//     boss.dashCooldown = 3.0f;
//     boss.dashSpeed = 500.0f;
//     boss.isDashing = false;
//     boss.isDead = false;
//     boss.deathAnimPlaying = false;
//     boss.deathFrame = 0;
//     boss.deathFrameCounter = 0;
//     boss.deathFrameTime = 0.12f;
//     boss.deathFinished = false;
//     boss.facingRight = false;
//     boss.zigzagTimer = 0.0f;
//     boss.zigzagAmplitude = 50.0f;
//     boss.zigzagFrequency = 2.0f;
//     boss.teleportTimer = 0.0f;
//     boss.teleportCooldown = 2.0f; // Reduced for phase 3
//     boss.isFlying = false;

//     Texture2D skill1 = LoadTexture("skill1.png");
//     Texture2D skill2 = LoadTexture("skill2.png");
//     Texture2D skill3 = LoadTexture("skill3.png");
//     Texture2D skill4 = LoadTexture("skill4.png");
//     Texture2D skill5 = LoadTexture("skill5.png");
//     Texture2D skill6 = LoadTexture("skill6.png");
//     Texture2D skill7 = LoadTexture("skill7.png"); // death sheet

//     boss.skillRight = skill1;
//     boss.skillLeft = skill2;

//     // Player setup
//     Player player = {0};
//     player.texture = LoadTexture("scarfy.png");
//     float playerScale = 0.4f;
//     player.position = (Vector2){200, GROUND_Y - player.texture.height * playerScale};
//     player.velocity = (Vector2){0, 0};
//     player.frame = 0;
//     player.frameTime = 0.15f;
//     player.frameCounter = 0;
//     player.facingRight = true;
//     player.isOnGround = true;
//     player.health = 2000;
//     player.alive = true;

//     // Projectiles
//     Projectile projectiles[MAX_PROJECTILES] = {0};
//     for (int i = 0; i < MAX_PROJECTILES; i++) {
//         projectiles[i].active = false;
//         projectiles[i].radius = 6.0f;
//     }

//     float proximityCooldown = 0.6f;
//     float proximityTimer = 0.0f;
//     int proximityDamage = 200;

//     float projSpeed = 400.0f;
//     float shootCooldown = 0.5f;
//     float shootTimer = 0.0f;

//     while (!WindowShouldClose()) {
//         float delta = GetFrameTime();
//         shootTimer += delta;

//         if (IsKeyPressed(KEY_ONE) && shootTimer >= shootCooldown) {
//             for (int i = 0; i < MAX_PROJECTILES; i++) {
//                 if (!projectiles[i].active) {
//                     projectiles[i].active = true;
//                     projectiles[i].position.x = player.position.x + (player.facingRight ? 40 : -10);
//                     projectiles[i].position.y = player.position.y + player.texture.height * 0.25f;
//                     projectiles[i].velocity.x = (player.facingRight ? 1 : -1) * projSpeed;
//                     projectiles[i].velocity.y = 0;
//                     shootTimer = 0.0f;
//                     break;
//                 }
//             }
//         }

//         for (int i = 0; i < MAX_PROJECTILES; i++) {
//             if (!projectiles[i].active) continue;
//             projectiles[i].position.x += projectiles[i].velocity.x * delta;
//             projectiles[i].position.y += projectiles[i].velocity.y * delta;

//             if (projectiles[i].position.x < -50 || projectiles[i].position.x > SCREEN_WIDTH + 50) {
//                 projectiles[i].active = false;
//             }
//         }

//         UpdatePlayer(&player, delta);

//         if (!boss.isDead) {
//             if (boss.phase == 1) {
//                 boss.skillRight = skill1;
//                 boss.skillLeft = skill2;
//             } else if (boss.phase == 2) {
//                 boss.skillRight = skill3;
//                 boss.skillLeft = skill4;
//             } else {
//                 boss.skillRight = skill5;
//                 boss.skillLeft = skill6;
//             }
//             UpdateBoss(&boss, delta, &player);
//         }

//         for (int i = 0; i < MAX_PROJECTILES; i++) {
//             if (!projectiles[i].active) continue;

//             float bossW = boss.skillRight.width / 6 * 1.8f;
//             float bossH = boss.skillRight.height * 1.8f;
//             Rectangle bossRect = { boss.position.x, boss.position.y, bossW, bossH };

//             Rectangle projRect = { projectiles[i].position.x - projectiles[i].radius,
//                                   projectiles[i].position.y - projectiles[i].radius,
//                                   projectiles[i].radius * 2, projectiles[i].radius * 2 };

//             if (CheckCollisionRecs(bossRect, projRect)) {
//                 projectiles[i].active = false;
//                 if (!boss.isDead) {
//                     boss.health -= 300;
//                     if (boss.health < 0) boss.health = 0;
//                 }
//             }
//         }

//         proximityTimer += delta;

//         if (proximityTimer >= proximityCooldown && !boss.isDead && player.alive) {
//             float pScale = 0.4f;
//             float pW = (player.texture.width / 6) * pScale;
//             float pH = player.texture.height * pScale;
//             Rectangle playerRect = { player.position.x, player.position.y, pW, pH };

//             float bScale = 1.8f;
//             float bW = (boss.skillRight.width / 6) * bScale;
//             float bH = boss.skillRight.height * bScale;
//             Rectangle bossRect = { boss.position.x, boss.position.y, bW, bH };

//             bool isAboveBoss = player.position.y + pH < boss.position.y;

//             if (CheckCollisionRecs(playerRect, bossRect) && !isAboveBoss) {
//                 player.health -= proximityDamage;
//                 if (player.health < 0) player.health = 0;
//                 proximityTimer = 0.0f;

//                 if (player.health <= 0) {
//                     player.alive = false;
//                 }
//             }
//         }

//         BeginDrawing();
//         ClearBackground(RAYWHITE);

//         DrawRectangle(0, GROUND_Y, SCREEN_WIDTH, SCREEN_HEIGHT - GROUND_Y, DARKGREEN);

//         DrawPlayer(&player);
//         DrawBoss(&boss, skill7);

//         for (int i = 0; i < MAX_PROJECTILES; i++) {
//             if (!projectiles[i].active) continue;
//             DrawCircleV(projectiles[i].position, projectiles[i].radius, BLACK);
//         }

//         int barWidth = 700;
//         int barHeight = 26;
//         int barX = (SCREEN_WIDTH - barWidth) / 2;
//         int barY = 18;

//         DrawRectangleLines(barX - 2, barY - 2, barWidth + 4, barHeight + 4, BLACK);
//         DrawRectangle(barX, barY, barWidth, barHeight, LIGHTGRAY);
//         float bossHealthRatio = (float)boss.health / 10000.0f;
//         if (bossHealthRatio < 0) bossHealthRatio = 0;
//         DrawRectangle(barX, barY, (int)(barWidth * bossHealthRatio), barHeight, RED);

//         char hpText[64];
//         sprintf(hpText, "BOSS HP: %d", boss.health);
//         int fontSize = 20;
//         Vector2 txtSize = MeasureTextEx(GetFontDefault(), hpText, fontSize, 0);
//         DrawText(hpText, barX + (barWidth - (int)txtSize.x) / 2, barY + (barHeight - fontSize) / 2, fontSize, BLACK);

//         int pBarWidth = 300;
//         int pBarHeight = 20;
//         int pBarX = 20;
//         int pBarY = SCREEN_HEIGHT - pBarHeight - 20;

//         DrawRectangleLines(pBarX - 2, pBarY - 2, pBarWidth + 4, pBarHeight + 4, BLACK);
//         DrawRectangle(pBarX, pBarY, pBarWidth, pBarHeight, LIGHTGRAY);
//         float playerHealthRatio = (float)player.health / 2000.0f;
//         if (playerHealthRatio < 0) playerHealthRatio = 0;
//         DrawRectangle(pBarX, pBarY, (int)(pBarWidth * playerHealthRatio), pBarHeight, RED);

//         char pText[64];
//         sprintf(pText, "SCARFY HP: %d", player.health);
//         DrawText(pText, pBarX + 6, pBarY - 22, 18, BLACK);

//         EndDrawing();
//     }

//     UnloadTexture(skill1);
//     UnloadTexture(skill2);
//     UnloadTexture(skill3);
//     UnloadTexture(skill4);
//     UnloadTexture(skill5);
//     UnloadTexture(skill6);
//     UnloadTexture(skill7);
//     UnloadTexture(player.texture);

//     CloseWindow();
//     return 0;
// }







//boss without player(2nd phase dash and zigzag, 3rd phase fly dash zigzag and teleport to random position)






#include "raylib.h"
#include "raymath.h"
#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define GROUND_Y 500   // Ground level

#define MAX_PROJECTILES 16

typedef struct Projectile {
    Vector2 position;
    Vector2 velocity;
    bool active;
    float radius;
} Projectile;

typedef struct Boss {
    Vector2 position;
    int health;
    float speed;
    int frame;
    float frameTime;
    float frameCounter;
    Texture2D skillRight;
    Texture2D skillLeft;
    int phase;
    bool facingRight;

    // Dash mechanic
    bool isDashing;
    float dashTimer;
    float dashCooldown;
    float dashSpeed;

    // Zigzag mechanic (Phase 2 and 3)
    float zigzagTimer;
    float zigzagAmplitude;
    float zigzagFrequency;

    // Teleport mechanic (Phase 2 and 3)
    float teleportTimer;
    float teleportCooldown;

    // Flying mechanic (Phase 3)
    bool isFlying;

    // Death animation
    bool isDead;
    bool deathAnimPlaying;
    int deathFrame;
    float deathFrameCounter;
    float deathFrameTime;
    bool deathFinished;
} Boss;

void UpdateBoss(Boss *boss, float delta) {
    if (boss->health <= 0) {
        boss->speed = 0;
        boss->isDashing = false;
        boss->isDead = true;
        return;
    }

    // Phase evolution
    if (boss->health > 5000) {
        boss->phase = 1;
        boss->speed = 100;
        boss->zigzagFrequency = 2.0f; // Default, not used in phase 1
        boss->isFlying = false;
    } else if (boss->health > 2000) {
        boss->phase = 2;
        boss->speed = 150;
        boss->zigzagFrequency = 2.0f; // Zigzag for phase 2
        boss->isFlying = false;
    } else {
        boss->phase = 3;
        boss->speed = 200;
        boss->zigzagFrequency = 2.0f; // Zigzag for phase 3
        boss->isFlying = true;
    }

    float bossWidth = (boss->skillRight.width / 6) * 1.8f;
    float bossHeight = (boss->skillRight.height) * 1.8f;
    float margin = 50.0f;
    float leftBound = margin;
    float rightBound = SCREEN_WIDTH - bossWidth - margin;
    float topBound = 50.0f;
    float bottomBound = boss->isFlying ? 300.0f : GROUND_Y - bossHeight;

    // Update timers
    boss->dashTimer += delta;
    boss->zigzagTimer += delta;
    boss->teleportTimer += delta;

    // Phase 3: Flying with zigzag, dash, and random teleport in sky
    if (boss->phase == 3) {
        // Random teleport in sky
        if (boss->teleportTimer >= boss->teleportCooldown) {
            if (rand() % 100 < 20) { // 20% chance to teleport
                boss->position.x = leftBound + (float)(rand() % (int)(rightBound - leftBound));
                boss->position.y = topBound + (float)(rand() % (int)(bottomBound - topBound));
            }
            boss->teleportTimer = 0.0f;
        }

        // Dash ability
        if (!boss->isDashing && boss->dashTimer >= boss->dashCooldown) {
            boss->isDashing = true;
            boss->dashTimer = 0;
        }

        if (boss->isDashing) {
            float dashDir = boss->facingRight ? 1 : -1;
            boss->position.x += dashDir * boss->dashSpeed * delta;
            if (boss->dashTimer > 0.5f) {
                boss->isDashing = false;
                boss->dashTimer = 0;
            }
        } else {
            // Zigzag movement in x and y
            float dir = boss->facingRight ? 1 : -1;
            boss->position.x += dir * boss->speed * delta;
            float zigzagOffsetX = boss->zigzagAmplitude * sinf(boss->zigzagTimer * boss->zigzagFrequency);
            boss->position.x += zigzagOffsetX;
            // Vertical oscillation for flying
            float zigzagOffsetY = boss->zigzagAmplitude * 0.5f * sinf(boss->zigzagTimer * boss->zigzagFrequency * 0.5f);
            boss->position.y += zigzagOffsetY;

            if (boss->position.x < leftBound) {
                boss->facingRight = true;
                boss->position.x = leftBound;
            }
            if (boss->position.x > rightBound) {
                boss->facingRight = false;
                boss->position.x = rightBound;
            }
        }

        // Clamp position to screen bounds
        boss->position.x = Clamp(boss->position.x, leftBound, rightBound);
        boss->position.y = Clamp(boss->position.y, topBound, bottomBound);
    }
    // Phase 2: Zigzag, dash, and random teleport on ground
    else if (boss->phase == 2) {
        // Random teleport on ground
        if (boss->teleportTimer >= boss->teleportCooldown) {
            boss->position.x = leftBound + (float)(rand() % (int)(rightBound - leftBound));
            boss->position.y = GROUND_Y - bossHeight;
            boss->teleportTimer = 0.0f;
        }

        // Dash ability
        if (!boss->isDashing && boss->dashTimer >= boss->dashCooldown) {
            boss->isDashing = true;
            boss->dashTimer = 0;
        }

        if (boss->isDashing) {
            float dashDir = boss->facingRight ? 1 : -1;
            boss->position.x += dashDir * boss->dashSpeed * delta;
            if (boss->dashTimer > 0.5f) {
                boss->isDashing = false;
                boss->dashTimer = 0;
            }
        } else {
            // Zigzag movement
            float dir = boss->facingRight ? 1 : -1;
            boss->position.x += dir * boss->speed * delta;
            float zigzagOffset = boss->zigzagAmplitude * sinf(boss->zigzagTimer * boss->zigzagFrequency);
            boss->position.x += zigzagOffset;

            if (boss->position.x < leftBound) {
                boss->facingRight = true;
                boss->position.x = leftBound;
            }
            if (boss->position.x > rightBound) {
                boss->facingRight = false;
                boss->position.x = rightBound;
            }
        }

        // Clamp position to screen bounds
        boss->position.x = Clamp(boss->position.x, leftBound, rightBound);
        boss->position.y = GROUND_Y - bossHeight; // Stay on ground
    }
    // Phase 1: Normal movement
    else if (boss->phase == 1) {
        float dir = boss->facingRight ? 1 : -1;
        boss->position.x += dir * boss->speed * delta;

        if (boss->position.x < leftBound) boss->facingRight = true;
        if (boss->position.x > rightBound) boss->facingRight = false;

        // Clamp position to screen bounds
        boss->position.x = Clamp(boss->position.x, leftBound, rightBound);
        boss->position.y = GROUND_Y - bossHeight;
    }

    // Frame animation
    boss->frameCounter += delta;
    if (boss->frameCounter >= boss->frameTime) {
        boss->frameCounter = 0;
        boss->frame++;
        if (boss->frame >= 6) boss->frame = 0;
    }
}

void DrawBoss(Boss *boss, Texture2D deathTex) {
    float scale = 1.8f;

    if (boss->isDead) {
        if (!boss->deathAnimPlaying && !boss->deathFinished) {
            boss->deathAnimPlaying = true;
            boss->deathFrame = 0;
            boss->deathFrameCounter = 0;
        }

        if (boss->deathAnimPlaying && !boss->deathFinished) {
            int cols = 10;
            int rows = 2;
            int frameWidth = deathTex.width / cols;
            int frameHeight = deathTex.height / rows;

            int currentRow = boss->deathFrame / cols;
            int currentCol = boss->deathFrame % cols;

            Rectangle source = {
                currentCol * frameWidth,
                currentRow * frameHeight,
                frameWidth,
                frameHeight
            };
            Rectangle dest = {
                boss->position.x,
                boss->position.y,
                frameWidth * scale,
                frameHeight * scale
            };

            DrawTexturePro(deathTex, source, dest, (Vector2){0,0}, 0, WHITE);

            boss->deathFrameCounter += GetFrameTime();
            if (boss->deathFrameCounter >= boss->deathFrameTime) {
                boss->deathFrameCounter = 0;
                boss->deathFrame++;
                if (boss->deathFrame >= cols * rows) {
                    boss->deathAnimPlaying = false;
                    boss->deathFinished = true;
                }
            }
        }
        return;
    }

    int frameWidth = boss->skillRight.width / 6;
    int frameHeight = boss->skillRight.height;
    Rectangle source = { boss->frame * frameWidth, 0, frameWidth, frameHeight };
    Rectangle dest = { boss->position.x, boss->position.y, frameWidth * scale, frameHeight * scale };

    Texture2D current = boss->facingRight ? boss->skillRight : boss->skillLeft;
    DrawTexturePro(current, source, dest, (Vector2){0,0}, 0, WHITE);
}

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Boss Battle");
    SetTargetFPS(60);

    SetRandomSeed((unsigned int)GetTime());

    // Boss setup
    Boss boss = {0};
    boss.position = (Vector2){500, GROUND_Y - 180};
    boss.health = 10000;
    boss.frame = 0;
    boss.frameTime = 0.15f;
    boss.frameCounter = 0;
    boss.dashCooldown = 3.0f;
    boss.dashSpeed = 500.0f;
    boss.isDashing = false;
    boss.isDead = false;
    boss.deathAnimPlaying = false;
    boss.deathFrame = 0;
    boss.deathFrameCounter = 0;
    boss.deathFrameTime = 0.12f;
    boss.deathFinished = false;
    boss.facingRight = false;
    boss.zigzagTimer = 0.0f;
    boss.zigzagAmplitude = 50.0f;
    boss.zigzagFrequency = 2.0f;
    boss.teleportTimer = 0.0f;
    boss.teleportCooldown = 2.0f; // Used for phase 3, phase 2 sets to 4.0f
    boss.isFlying = false;

    Texture2D skill1 = LoadTexture("skill1.png");
    Texture2D skill2 = LoadTexture("skill2.png");
    Texture2D skill3 = LoadTexture("skill3.png");
    Texture2D skill4 = LoadTexture("skill4.png");
    Texture2D skill5 = LoadTexture("skill5.png");
    Texture2D skill6 = LoadTexture("skill6.png");
    Texture2D skill7 = LoadTexture("skill7.png"); // death sheet

    boss.skillRight = skill1;
    boss.skillLeft = skill2;

    // Projectiles
    Projectile projectiles[MAX_PROJECTILES] = {0};
    for (int i = 0; i < MAX_PROJECTILES; i++) {
        projectiles[i].active = false;
        projectiles[i].radius = 6.0f;
    }

    while (!WindowShouldClose()) {
        float delta = GetFrameTime();

        // Update projectiles
        for (int i = 0; i < MAX_PROJECTILES; i++) {
            if (!projectiles[i].active) continue;
            projectiles[i].position.x += projectiles[i].velocity.x * delta;
            projectiles[i].position.y += projectiles[i].velocity.y * delta;

            if (projectiles[i].position.x < -50 || projectiles[i].position.x > SCREEN_WIDTH + 50) {
                projectiles[i].active = false;
            }
        }

        if (!boss.isDead) {
            if (boss.phase == 1) {
                boss.skillRight = skill1;
                boss.skillLeft = skill2;
            } else if (boss.phase == 2) {
                boss.skillRight = skill3;
                boss.skillLeft = skill4;
                boss.teleportCooldown = 4.0f; // Set for phase 2
            } else {
                boss.skillRight = skill5;
                boss.skillLeft = skill6;
                boss.teleportCooldown = 2.0f; // Set for phase 3
            }
            UpdateBoss(&boss, delta);
        }

        // Check projectile collisions with boss
        for (int i = 0; i < MAX_PROJECTILES; i++) {
            if (!projectiles[i].active) continue;

            float bossW = boss.skillRight.width / 6 * 1.8f;
            float bossH = boss.skillRight.height * 1.8f;
            Rectangle bossRect = { boss.position.x, boss.position.y, bossW, bossH };

            Rectangle projRect = { projectiles[i].position.x - projectiles[i].radius,
                                  projectiles[i].position.y - projectiles[i].radius,
                                  projectiles[i].radius * 2, projectiles[i].radius * 2 };

            if (CheckCollisionRecs(bossRect, projRect)) {
                projectiles[i].active = false;
                if (!boss.isDead) {
                    boss.health -= 300;
                    if (boss.health < 0) boss.health = 0;
                }
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawRectangle(0, GROUND_Y, SCREEN_WIDTH, SCREEN_HEIGHT - GROUND_Y, DARKGREEN);

        DrawBoss(&boss, skill7);

        for (int i = 0; i < MAX_PROJECTILES; i++) {
            if (!projectiles[i].active) continue;
            DrawCircleV(projectiles[i].position, projectiles[i].radius, BLACK);
        }

        int barWidth = 700;
        int barHeight = 26;
        int barX = (SCREEN_WIDTH - barWidth) / 2;
        int barY = 18;

        DrawRectangleLines(barX - 2, barY - 2, barWidth + 4, barHeight + 4, BLACK);
        DrawRectangle(barX, barY, barWidth, barHeight, LIGHTGRAY);
        float bossHealthRatio = (float)boss.health / 10000.0f;
        if (bossHealthRatio < 0) bossHealthRatio = 0;
        DrawRectangle(barX, barY, (int)(barWidth * bossHealthRatio), barHeight, RED);

        char hpText[64];
        sprintf(hpText, "BOSS HP: %d", boss.health);
        int fontSize = 20;
        Vector2 txtSize = MeasureTextEx(GetFontDefault(), hpText, fontSize, 0);
        DrawText(hpText, barX + (barWidth - (int)txtSize.x) / 2, barY + (barHeight - fontSize) / 2, fontSize, BLACK);

        EndDrawing();
    }

    UnloadTexture(skill1);
    UnloadTexture(skill2);
    UnloadTexture(skill3);
    UnloadTexture(skill4);
    UnloadTexture(skill5);
    UnloadTexture(skill6);
    UnloadTexture(skill7);

    CloseWindow();
    return 0;

}
