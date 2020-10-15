[1mdiff --git a/Const.h b/Const.h[m
[1mindex 5c88fb7..ea7a577 100644[m
[1m--- a/Const.h[m
[1m+++ b/Const.h[m
[36m@@ -24,7 +24,7 @@[m [mnamespace ScenePriority {[m
     static const int spaceship = 10;         //default Zvalue is 0[m
     static const int fullScreenText = 20;[m
     static const int bullet = 15;[m
[31m-    static const int scoreBar = 15;[m
[32m+[m[32m    static const int text = 30;[m
 }[m
 [m
 namespace Side {[m
[1mdiff --git a/Enemy.cpp b/Enemy.cpp[m
[1mindex 36d9cc5..cba27b0 100644[m
[1m--- a/Enemy.cpp[m
[1m+++ b/Enemy.cpp[m
[36m@@ -6,7 +6,7 @@[m
 #include <cmath>[m
 #include "Const.h"[m
 [m
[31m-Enemy::Enemy(EnemyManager *manager, QString imagePath) : SpaceShip(manager, imagePath)[m
[32m+[m[32mEnemy::Enemy(EnemyManager *manager, QString imagePath, int count) : SpaceShip(manager, imagePath)[m
 {[m
     bulletSpeed = -10;[m
     shootDelay = baseShootDelay;[m
[36m@@ -15,12 +15,15 @@[m [mEnemy::Enemy(EnemyManager *manager, QString imagePath) : SpaceShip(manager, imag[m
     xSpeed = int(std::rand() % 21 - 10);[m
     ySpeed = int(std::rand() % 3 + 1);[m
 [m
[32m+[m
     this->manager = manager;[m
[32m+[m[32m    this->count = count;[m
 [m
     setUpDelay(shootDelay);[m
 [m
     connect(manager,SIGNAL(changeDifficulty(int)),this,SLOT(setDifficulty(int)));[m
     connect(this, SIGNAL(enemyOnBase()),manager, SIGNAL(enemyOnBase()));[m
[32m+[m[32m    connect(manager, SIGNAL(logKeyPressed(bool)), this, SLOT(toggleCheckText(bool)));[m
 }[m
 [m
 Enemy::~Enemy(){ [m
[36m@@ -40,8 +43,20 @@[m [mvoid Enemy::onTimer(){[m
     }[m
 }[m
 [m
[32m+[m[32mvoid Enemy::groupCheckTextInfo()[m
[32m+[m[32m{[m
[32m+[m[32m    QString output = "";[m
[32m+[m[32m    output += "Count : " + QString::number(count) + "\n";[m
[32m+[m[32m    output += "Diff  : " + QString::number(difficulty) + "\n";[m
[32m+[m[32m    output += "Bull speed : " + QString::number(bulletSpeed) + "\n";[m
[32m+[m[32m    output += "Speed: x: " + QString::number(xSpeed) + " y: " + QString::number(ySpeed) + "\n";[m
[32m+[m[32m    setCheckText(output);[m
[32m+[m[32m}[m
[32m+[m
 void Enemy::setDifficulty(int difficulty)[m
 {[m
[32m+[m[32m    this->difficulty = difficulty;[m
[32m+[m
     shootDelay = baseShootDelay * pow(0.8, difficulty-1);[m
     setUpDelay(shootDelay);[m
     bulletSpeed = baseBulletSpeed * difficulty;[m
[36m@@ -59,7 +74,7 @@[m [mvoid Enemy::move()[m
 [m
     setPos(x() + xSpeed, y() + ySpeed);[m
 [m
[31m-[m
[32m+[m[32m    groupCheckTextInfo();[m
 }[m
 [m
 void Enemy::positiveRemoval(int hitBy)[m
[36m@@ -73,5 +88,3 @@[m [mvoid Enemy::positiveRemoval(int hitBy)[m
     delete this;[m
 }[m
 [m
[31m-[m
[31m-[m
[1mdiff --git a/ScoreBar.cpp b/ScoreBar.cpp[m
[1mindex 064afed..66d6ef0 100644[m
[1m--- a/ScoreBar.cpp[m
[1m+++ b/ScoreBar.cpp[m
[36m@@ -10,7 +10,7 @@[m [mScoreBar::ScoreBar()[m
     this->setFont(font);[m
     this->setDefaultTextColor(color);[m
     this->setPlainText(QString::number(0));[m
[31m-    this->setZValue(ScenePriority::scoreBar);[m
[32m+[m[32m    this->setZValue(ScenePriority::text);[m
 }[m
 [m
 void ScoreBar::setScore(int new_score)[m
[1mdiff --git a/enemy.h b/enemy.h[m
[1mindex d9a9ec6..854a297 100644[m
[1m--- a/enemy.h[m
[1m+++ b/enemy.h[m
[36m@@ -10,7 +10,7 @@[m
 class Enemy: public SpaceShip{[m
     Q_OBJECT[m
 public:[m
[31m-    Enemy(EnemyManager* manager, QString imagePath);[m
[32m+[m[32m    Enemy(EnemyManager* manager, QString imagePath, int count);[m
     ~Enemy();[m
     int type() const override{[m
         return Keys::enemyIndex;[m
[36m@@ -18,11 +18,14 @@[m [mpublic:[m
 [m
 public slots:[m
     void onTimer() override;[m
[32m+[m[32m    void groupCheckTextInfo() override;[m
     void setDifficulty(int difficulty);[m
 [m
 private:[m
     const int baseBulletSpeed = -10;[m
     EnemyManager* manager;[m
[32m+[m[32m    int count;[m
[32m+[m[32m    int difficulty;[m
 [m
     void move();[m
     void positiveRemoval(int hitType);[m
[1mdiff --git a/enemymanager.cpp b/enemymanager.cpp[m
[1mindex 0a06738..527a8ca 100644[m
[1m--- a/enemymanager.cpp[m
[1m+++ b/enemymanager.cpp[m
[36m@@ -8,12 +8,13 @@[m
 #include <cstdlib>[m
 #include "Const.h"[m
 [m
[31m-EnemyManager::EnemyManager(QGraphicsScene *scene, ScoreBar *scoreBar)[m
[32m+[m[32mEnemyManager::EnemyManager(QGraphicsScene* scene, ScoreBar* scoreBar, KeyManager* keyManager)[m
 {[m
     this->scene = scene;[m
     this->scoreBar = scoreBar;[m
[31m-    QTimer * timer = new QTimer();[m
[32m+[m[32m    QTimer* timer = new QTimer();[m
     connect(timer,SIGNAL(timeout()),this,SLOT(onTimer()));[m
[32m+[m[32m    connect(keyManager, SIGNAL(logKeyPressed(bool)), this, SIGNAL(logKeyPressed(bool)));[m
 [m
     timer->start(2000);[m
 }[m
[36m@@ -58,13 +59,12 @@[m [mvoid EnemyManager::onTimer()[m
 [m
 void EnemyManager::createEnemy()[m
 {[m
[31m-    Enemy * enemy = new Enemy(this, ImagePaths::enemyImagePath);[m
[32m+[m[32m    Enemy * enemy = new Enemy(this, ImagePaths::enemyImagePath, enemyCount);[m
     scene->addItem(enemy);[m
     int offset = 100;[m
     // 0...800[m
     // 100...700[m
     // 0...(800-2*100)[m
[31m-    enemy->setPos(int(std::rand() % (int(scene->width()) - 2*offset) + offset), 0);[m
[32m+[m[32m    enemy->setPos(int(std::rand() % (int(scene->width()) - 2*offset) + offset), 0);[m[41m  [m
     enemyCount++;[m
[31m-[m
 }[m
[1mdiff --git a/enemymanager.h b/enemymanager.h[m
[1mindex b9584fe..ca5f729 100644[m
[1m--- a/enemymanager.h[m
[1m+++ b/enemymanager.h[m
[36m@@ -4,6 +4,7 @@[m
 #include <QObject>[m
 #include <QGraphicsRectItem>[m
 #include "ScoreBar.h"[m
[32m+[m[32m#include "keymanager.h"[m
 [m
 class Enemy;[m
 [m
[36m@@ -11,7 +12,7 @@[m [mclass EnemyManager : public QObject, public QGraphicsRectItem[m
 {[m
     Q_OBJECT[m
 public:[m
[31m-    EnemyManager(QGraphicsScene *scene, ScoreBar *scoreBar);[m
[32m+[m[32m    EnemyManager(QGraphicsScene* scene, ScoreBar* scoreBar, KeyManager* keyManager);[m
     void onEnemyDestruction(Enemy* enemy);[m
     void onKillByHero(Enemy* enemy);[m
     void onKillByNonHero(Enemy* enemy);[m
[36m@@ -21,6 +22,7 @@[m [msignals:[m
     void changeDifficulty(int difficulty);[m
     void allEnemiesDefeated();[m
     void enemyOnBase();[m
[32m+[m[32m    void logKeyPressed(bool);[m
 [m
 public slots:[m
     void onTimer();[m
[1mdiff --git a/gamemanager.cpp b/gamemanager.cpp[m
[1mindex 6f135ea..14f3116 100644[m
[1m--- a/gamemanager.cpp[m
[1m+++ b/gamemanager.cpp[m
[36m@@ -18,7 +18,7 @@[m [mGameManager::GameManager(QObject *parent) : QObject(parent)[m
 [m
     view = new GraphicsView(scene);[m
     KeyManager* keyManager = new KeyManager();[m
[31m-    EnemyManager* enemyManager = new EnemyManager(scene,scoreBar);[m
[32m+[m[32m    EnemyManager* enemyManager = new EnemyManager(scene, scoreBar, keyManager);[m
     hero = new Hero(ImagePaths::heroImagePath, keyManager);[m
 [m
     scoreBar = new ScoreBar();[m
[1mdiff --git a/hero.cpp b/hero.cpp[m
[1mindex 01da66a..ce58365 100644[m
[1m--- a/hero.cpp[m
[1m+++ b/hero.cpp[m
[36m@@ -21,6 +21,7 @@[m [mHero::Hero(QString imagePath, KeyManager* keyManager) : SpaceShip(nullptr, image[m
 [m
     this->keyManager = keyManager;[m
     connect(keyManager, SIGNAL(heroKeyPressed(int)), this, SLOT(heroKeyPressed(int)));[m
[32m+[m[32m    connect(keyManager, SIGNAL(logKeyPressed(bool)), this, SLOT(toggleCheckText(bool)));[m
 }[m
 [m
 void Hero::onTimer()[m
[36m@@ -30,6 +31,11 @@[m [mvoid Hero::onTimer()[m
     }[m
 }[m
 [m
[32m+[m[32mvoid Hero::groupCheckTextInfo()[m
[32m+[m[32m{[m
[32m+[m
[32m+[m[32m}[m
[32m+[m
 void Hero::heroKeyPressed(int key)[m
 {[m
     //qDebug() << "key pressed";[m
[1mdiff --git a/hero.h b/hero.h[m
[1mindex 5c6c292..bc01cf9 100644[m
[1m--- a/hero.h[m
[1m+++ b/hero.h[m
[36m@@ -19,6 +19,7 @@[m [msignals:[m
 [m
 public slots:[m
     void onTimer() override;[m
[32m+[m[32m    void groupCheckTex