/*
Copyright (c) 2018 Brian Lough. All right reserved.

UniversalTelegramBot - Library to create your own Telegram Bot using
ESP8266 or ESP32 on Arduino IDE.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/

#include "UniversalTelegramBot.h"
#include "UniversalTelegramBotTypes.h"
#include <Arduino.h>

  TelegramUser* TelegramUser::fromJsonObject(JsonObject jsonFrom)
  {
    this->id = jsonFrom["id"].as<int64_t>();
    this->is_bot = jsonFrom["is_bot"].as<bool>();
    this->first_name = jsonFrom["first_name"].as<String>();
    this->last_name = jsonFrom["last_name"].as<String>();
    this->username = jsonFrom["username"].as<String>();
    this->language_code = jsonFrom["language_code"].as<String>();
    this->can_join_groups = jsonFrom["can_join_groups"].as<bool>();
    this->can_read_all_group_messages = jsonFrom["can_read_all_group_messages"].as<bool>();
    this->supports_inline_queries = jsonFrom["supports_inline_queries"].as<bool>();

    return this;
  }

  String TelegramUser::getPublicName()
  {
    return this->first_name + " " + (this->username.length() > 0 ? "@" + this->username : "");
  }

  TelegramChatPhoto* TelegramChatPhoto::fromJsonObject(JsonObject jsonObject)
  {
    this->small_file_id = jsonObject["small_file_id"].as<String>();
    this->small_file_unique_id = jsonObject["small_file_unique_id"].as<String>();
    this->big_file_id = jsonObject["big_file_id"].as<String>();
    this->big_file_unique_id = jsonObject["big_file_unique_id"].as<String>();
    return this;
  }

  TelegramChatPermissions* TelegramChatPermissions::fromJsonObject(JsonObject jsonObject)
  {
    this->can_send_messages = jsonObject["can_send_messages"].as<bool>();
    this->can_send_media_messages = jsonObject["can_send_media_messages"].as<bool>();
    this->can_send_polls = jsonObject["can_send_polls"].as<bool>();
    this->can_send_other_messages = jsonObject["can_send_other_messages"].as<bool>();
    this->can_add_web_page_previews = jsonObject["can_add_web_page_previews"].as<bool>();
    this->can_change_info = jsonObject["can_change_info"].as<bool>();
    this->can_invite_users = jsonObject["can_invite_users"].as<bool>();
    this->can_pin_messages = jsonObject["can_pin_messages"].as<bool>();

    return this;
  }

  TelegramLocation* TelegramLocation::fromJsonObject(JsonObject jsonObject)
  {
      this->longitude = jsonObject["longitude"].as<float>();
      this->latitude = jsonObject["latitude"].as<float>();
      this->horizontal_accuracy = jsonObject["horizontal_accuracy"].as<float>();
      this->live_period = jsonObject["live_period"].as<int>();
      this->heading = jsonObject["heading"].as<int>();
      this->proximity_alert_radius = jsonObject["proximity_alert_radius"].as<int>();

      return this;
  }

  TelegramChatLocation::~TelegramChatLocation() {
    if (this->location) {
      delete this->location;
      this->location = NULL;
    }
  }

  TelegramChatLocation* TelegramChatLocation::fromJsonObject(JsonObject jsonObject)
  {
    if (jsonObject.containsKey("location")) {
      TelegramLocation *location = new TelegramLocation;
      this->location = location->fromJsonObject(jsonObject["location"]);
    }

    this->address = jsonObject["address"].as<String>();

    return this;
  }

  TelegramChat::~TelegramChat() {
    if (photo) {
      delete photo;
      photo = NULL;
    }
    if (pinned_message) {
      delete pinned_message;
      pinned_message = NULL;
    }
    if (permissions) {
      delete permissions;
      permissions = NULL;
    }
    if (location) {
      delete location;
      location = NULL;
    }
  }

  TelegramChat* TelegramChat::fromJsonObject(JsonObject jsonObject) 
  {
    this->id = jsonObject["id"].as<int64_t>();
    this->type = jsonObject["type"].as<String>();
    this->title = jsonObject["title"].as<String>();
    this->username = jsonObject["username"].as<String>();
    this->first_name = jsonObject["first_name"].as<String>();
    this->last_name = jsonObject["last_name"].as<String>();

    if (jsonObject.containsKey("photo")) {
      TelegramChatPhoto *photo = new TelegramChatPhoto();
      this->photo = photo->fromJsonObject(jsonObject["photo"]);
    }

    this->bio = jsonObject["bio"].as<String>();
    this->description = jsonObject["description"].as<String>();
    this->invite_link = jsonObject["invite_link"].as<String>();

    if (jsonObject.containsKey("pinned_message")) {
      TelegramMessage *telegramPinnedMessage = new TelegramMessage();
      this->pinned_message = telegramPinnedMessage->fromJsonObject(jsonObject["pinned_message"]);
    }

    if (jsonObject.containsKey("permissions")) {
      TelegramChatPermissions *chatPermissions = new TelegramChatPermissions;
      this->permissions = chatPermissions->fromJsonObject(jsonObject["permissions"]);
    }

    this->slow_mode_delay = jsonObject["slow_mode_delay"].as<int>();
    this->message_auto_delete_time = jsonObject["message_auto_delete_time"].as<int>();
    this->sticker_set_name = jsonObject["sticker_set_name"].as<String>();
    this->can_set_sticker_set = jsonObject["can_set_sticker_set"].as<bool>();
    this->linked_chat_id = jsonObject["linked_chat_id"].as<int64_t>();

    if (jsonObject.containsKey("location")) {
      TelegramChatLocation *chatLocation = new TelegramChatLocation;
      this->location = chatLocation->fromJsonObject(jsonObject["location"]);
    }

    return this;
  }

  TelegramMessageEntity::~TelegramMessageEntity() {
    if (this->user) {
      delete this->user;
      this->user = NULL;
    }
  }

  TelegramMessage::~TelegramMessage() {
    if (from) {
      delete from;
      from = NULL;
    }
    if (sender_chat) {
      delete sender_chat;
      sender_chat = NULL;
    }
    if (chat) {
      delete chat;
      chat = NULL;
    }
    if (forward_from) {
      delete forward_from;
      forward_from = NULL;
    }
    if (forward_from_chat) {
      delete forward_from_chat;
      forward_from_chat = NULL;
    }
    if (reply_to_message) {
      delete reply_to_message;
      reply_to_message = NULL;
    }
    if (via_bot) {
      delete via_bot;
      via_bot = NULL;
    }
    if (entities) {
      delete[] entities;
      entities = NULL;
      entities_size = 0;
    }
    if (caption_entities) {
      delete[] caption_entities;
      caption_entities = NULL;
      caption_entities_size = 0;
    }
    if (location) {
      delete location;
      location = NULL;
    }
    if (new_chat_members) {
      delete[] new_chat_members;
      new_chat_members = NULL;
      new_chat_members_size = 0;
    }
    if (left_chat_member) {
      delete left_chat_member;
      left_chat_member = NULL;
    }
    if (pinned_message) {
      delete pinned_message;
      pinned_message = NULL;
    }
  }

  TelegramMessage* TelegramMessage::fromJsonObject(JsonObject jsonObject) 
  {
    this->message_id = jsonObject["message_id"].as<int>();

    if (jsonObject.containsKey("from")) {
      TelegramUser *from = new TelegramUser;
      this->from = from->fromJsonObject(jsonObject["from"]);
    }

    if (jsonObject.containsKey("sender_chat")) {
      TelegramChat *sender_chat = new TelegramChat;
      this->sender_chat = sender_chat->fromJsonObject(jsonObject["sender_chat"]);
    }

    this->date = jsonObject["date"].as<int>();
    TelegramChat *chat = new TelegramChat;
    this->chat = chat->fromJsonObject(jsonObject["chat"]);

    if (jsonObject.containsKey("forward_from")) {
      TelegramUser *forward_from = new TelegramUser;
      this->forward_from = forward_from->fromJsonObject(jsonObject["forward_from"]);
    }

    if (jsonObject.containsKey("forward_from_chat")) {
      TelegramChat *forward_from_chat = new TelegramChat;
      this->forward_from_chat = forward_from_chat->fromJsonObject(jsonObject["forward_from_chat"]);
    }

    this->forward_from_message_id = jsonObject["forward_from_message_id"].as<int>();
    this->forward_signature = jsonObject["forward_signature"].as<String>();
    this->forward_sender_name = jsonObject["forward_sender_name"].as<String>();
    this->forward_date = jsonObject["forward_date"].as<int>();

    if (jsonObject.containsKey("reply_to_message")) {
      TelegramMessage *replyMessage = new TelegramMessage;
      replyMessage->message_id = jsonObject["reply_to_message"]["message_id"].as<int>();
      replyMessage->date = jsonObject["reply_to_message"]["date"].as<int>();
      TelegramChat *reply_chat = new TelegramChat;
      replyMessage->chat = reply_chat->fromJsonObject(jsonObject["reply_to_message"]["chat"]);
      this->reply_to_message = replyMessage;
    }

    if (jsonObject.containsKey("via_bot")) {
      TelegramUser *via_bot = new TelegramUser;
      this->via_bot = via_bot->fromJsonObject(jsonObject["via_bot"]);
    }

    this->edit_date = jsonObject["edit_data"].as<int>();
    this->media_group_id = jsonObject["media_group_id"].as<String>();
    this->author_signature = jsonObject["author_signature"].as<String>();
    this->text = jsonObject["text"].as<String>();
    this->caption = jsonObject["caption"].as<String>();

    if (jsonObject.containsKey("new_chat_members")) {
      JsonArray array = jsonObject["new_chat_members"].as<JsonArray>();
      Serial.println(jsonObject["new_chat_members"].as<String>());
      Serial.println("size:" + String(array.size()));
      TelegramUser *users = new TelegramUser[array.size()];
      int index = 0;
      for(JsonVariant v : array) {
        Serial.println("parse user index:" + String(index));
        TelegramUser *newComer = new TelegramUser;
        users[index++] = *newComer->fromJsonObject(v.as<JsonObject>());
      }
      this->new_chat_members = users;
      this->new_chat_members_size = array.size();
    }

    if (jsonObject.containsKey("left_chat_member")) {
        TelegramUser *left_chat_member = new TelegramUser;
      this->left_chat_member = left_chat_member->fromJsonObject(jsonObject["left_chat_member"]);
    }

    this->new_chat_title = jsonObject["new_chat_title"].as<String>();

    this->delete_chat_photo = jsonObject["delete_chat_photo"].as<String>();
    this->group_chat_created = jsonObject["group_chat_created"].as<String>();
    this->supergroup_chat_created = jsonObject["supergroup_chat_created"].as<String>();
    this->channel_chat_created = jsonObject["channel_chat_created"].as<String>();

    this->migrate_to_chat_id = jsonObject["migrate_to_chat_id"].as<int64_t>();
    this->migrate_from_chat_id = jsonObject["migrate_from_chat_id"].as<int64_t>();

    this->connected_website = jsonObject["connected_website"].as<String>();

    return this;
  }

  TelegramInlineQuery::~TelegramInlineQuery() {
    if (from) {
      delete from;
      from = NULL;
    }

    if (location) {
      delete location;
      location = NULL;
    }
  }

  TelegramCallbackQuery::~TelegramCallbackQuery() {
    if (from) {
      delete from;
      from = NULL;
    }
    if (message) {
      delete message;
      message = NULL;
    }
  }

  TelegramCallbackQuery* TelegramCallbackQuery::fromJsonObject(JsonObject jsonObject) {
    this->id = jsonObject["id"].as<String>();

    if (jsonObject.containsKey("from")) {
      TelegramUser* from = new TelegramUser;
      this->from = from->fromJsonObject(jsonObject["from"]);
    }

    if (jsonObject.containsKey("message")) {
      TelegramMessage* message = new TelegramMessage;
      this->message = message->fromJsonObject(jsonObject["message"]);
    }

    this->inline_message_id = jsonObject["inline_message_id"].as<String>();
    this->chat_instance = jsonObject["chat_instance"].as<String>();
    this->data = jsonObject["data"].as<String>();
    this->game_short_name = jsonObject["game_short_name"].as<String>();

    return this;
  }

  TelegramChatMember::~TelegramChatMember() {
    if (user) {
      delete user;
      user = NULL;
    }
  }

  TelegramChatInviteLink::~TelegramChatInviteLink() {
    if (creator) {
      delete creator;
      creator = NULL;
    }
  }

  TelegramChatMemberUpdated::~TelegramChatMemberUpdated() {
    if (chat) {
      delete chat;
      chat = NULL;
    }
    if (user) {
      delete user;
      user = NULL;
    }
    if (old_chat_member) {
      delete old_chat_member;
      old_chat_member = NULL;
    }
    if (new_chat_member) {
      delete new_chat_member;
      new_chat_member = NULL;
    }
    if (invite_link) {
      delete invite_link;
      invite_link = NULL;
    }
  }

  TelegramUpdate::~TelegramUpdate() {
    if (message) {
      delete message;
      message = NULL;
    }
    if (edited_message) {
      delete edited_message;
      edited_message = NULL;
    }
    if (channel_post) {
      delete channel_post;
      channel_post = NULL;
    }
    if (edited_channel_post) {
      delete edited_channel_post;
      edited_channel_post = NULL;
    }
    if (inline_query) {
      delete inline_query;
      inline_query = NULL;
    }
    if (callback_query) {
      delete callback_query;
      callback_query = NULL;
    }
  }
