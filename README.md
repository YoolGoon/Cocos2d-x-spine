# spine
Read Spine file other forder

EX)
SkeletonAnimation * skUnit_Upgrade = SkeletonAnimation::createWithFile_Not_Assets(fileName_json->getCString(), fileName_atlas->getCString(), true, 1.0f);
skUnit_Upgrade->setAnimation(0, "normal", false);
skUnit_Upgrade->setPosition(SToneEngine::GetInstance().CENTER_POINT);
this->addChild(skUnit_Upgrade);

