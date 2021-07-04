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

#ifndef UniversalTelegramBotTypes_h
#define UniversalTelegramBotTypes_h

#include <Arduino.h>

struct TelegramUser {
  int64_t id;   // Unique identifier for this user or bot.
  bool is_bot;  // True, if this user is a bot
  String first_name;  // User's or bot's first name
  String last_name = "";   // Optional. User's or bot's last name
  String username = "";    // Optional. User's or bot's username
  String language_code = ""; // Optional. IETF language tag of the user's language
  bool can_join_groups = "";   // Optional. True, if the bot can be invited to groups. Returned only in getMe.
  bool can_read_all_group_messages = ""; // Optional. True, if privacy mode is disabled for the bot. Returned only in getMe.
  bool supports_inline_queries = ""; // Optional. True, if the bot supports inline queries. Returned only in getMe.

  TelegramUser* fromJsonObject(JsonObject jsonFrom);
  String getPublicName();
};

struct TelegramChatPhoto {
  String small_file_id;
  String small_file_unique_id;
  String big_file_id;
  String big_file_unique_id;

  TelegramChatPhoto* fromJsonObject(JsonObject jsonObject);
};

struct TelegramChatPermissions {
  bool can_send_messages = false; // Optional. True, if the user is allowed to send text messages, contacts, locations and venues
  bool can_send_media_messages = false; // Optional. True, if the user is allowed to send audios, documents, photos, videos, video notes and voice notes, implies can_send_messages
  bool can_send_polls = false; // Optional. True, if the user is allowed to send polls, implies can_send_messages
  bool can_send_other_messages = false; // Optional. True, if the user is allowed to send animations, games, stickers and use inline bots, implies can_send_media_messages
  bool can_add_web_page_previews = false; // Optional. True, if the user is allowed to add web page previews to their messages, implies can_send_media_messages
  bool can_change_info = false; // Optional. True, if the user is allowed to change the chat title, photo and other settings. Ignored in public supergroups
  bool can_invite_users = false; // Optional. True, if the user is allowed to invite new users to the chat
  bool can_pin_messages = false; // Optional. True, if the user is allowed to pin messages. Ignored in public supergroups

  TelegramChatPermissions* fromJsonObject(JsonObject jsonObject);
};

struct TelegramLocation {
  float longitude; // Longitude as defined by sender
  float latitude; // Latitude as defined by sender
  float horizontal_accuracy = 0; // Optional. The radius of uncertainty for the location, measured in meters; 0-1500
  int live_period = 0; // Optional. Time relative to the message sending date, during which the location can be updated, in seconds. For active live locations only.
  int heading = 0; // Optional. The direction in which user is moving, in degrees; 1-360. For active live locations only.
  int proximity_alert_radius = 0; // Optional. Maximum distance for proximity alerts about approaching another chat member, in meters. For sent live locations only.
  
  TelegramLocation* fromJsonObject(JsonObject jsonObject);
};

struct TelegramChatLocation {
  TelegramLocation *location; // The location to which the supergroup is connected. Can't be a live location.
  String address; // Location address; 1-64 characters, as defined by the chat owner

  ~TelegramChatLocation();
  TelegramChatLocation* fromJsonObject(JsonObject jsonObject);
};

struct TelegramChat {
  int64_t id; // Unique identifier for this chat. 
  String type; // Type of chat, can be either “private”, “group”, “supergroup” or “channel”
  String title = ""; // Optional. Title, for supergroups, channels and group chats
  String username = ""; // Optional. Username, for private chats, supergroups and channels if available
  String first_name = ""; // Optional. First name of the other party in a private chat
  String last_name = ""; // Optional. Last name of the other party in a private chat
  TelegramChatPhoto *photo = NULL; // Optional. Chat photo. Returned only in getChat.
  String bio = ""; // Optional. Bio of the other party in a private chat. Returned only in getChat.
  String description = ""; // Optional. Description, for groups, supergroups and channel chats. Returned only in getChat.
  String invite_link = ""; // Optional. Primary invite link, for groups, supergroups and channel chats. Returned only in getChat.
  struct TelegramMessage *pinned_message = NULL; // Optional. The most recent pinned message (by sending date). Returned only in getChat.
  TelegramChatPermissions *permissions = NULL; // Optional. Default chat member permissions, for groups and supergroups. Returned only in getChat.
  int slow_mode_delay = 0; // Optional. For supergroups, the minimum allowed delay between consecutive messages sent by each unpriviledged user. Returned only in getChat.
  int message_auto_delete_time = 0; // Optional. The time after which all messages sent to the chat will be automatically deleted; in seconds. Returned only in getChat.
  String sticker_set_name = ""; // Optional. For supergroups, name of group sticker set. Returned only in getChat.
  bool can_set_sticker_set = ""; // Optional. True, if the bot can change the group sticker set. Returned only in getChat.
  int64_t linked_chat_id = 0; // Optional. Unique identifier for the linked chat, i.e. the discussion group identifier for a channel and vice versa; for supergroups and channel chats.
  TelegramChatLocation *location = NULL; // Optional. For supergroups, the location to which the supergroup is connected. Returned only in getChat.

  ~TelegramChat();

  TelegramChat* fromJsonObject(JsonObject jsonObject);
};

struct TelegramMessageEntity {
  String type; // Type of the entity. Can be “mention” (@username), “hashtag” (#hashtag), “cashtag” ($USD), “bot_command” (/start@jobs_bot), “url” (https://telegram.org), “email” (do-not-reply@telegram.org), “phone_number” (+1-212-555-0123), “bold” (bold text), “italic” (italic text), “underline” (underlined text), “strikethrough” (strikethrough text), “code” (monowidth string), “pre” (monowidth block), “text_link” (for clickable text URLs), “text_mention” (for users without usernames)
  int offset; // Offset in UTF-16 code units to the start of the entity
  int length; // Length of the entity in UTF-16 code units
  String url = ""; // Optional. For “text_link” only, url that will be opened after user taps on the text
  TelegramUser *user = NULL; // User	Optional. For “text_mention” only, the mentioned user
  String language = ""; // Optional. For “pre” only, the programming language of the entity text

  ~TelegramMessageEntity();
};

struct TelegramMessage {
  int message_id = 0; // Unique message identifier inside this chat
  TelegramUser *from = NULL; // Optional. Sender, empty for messages sent to channels
  TelegramChat *sender_chat = NULL; // Optional. Sender of the message, sent on behalf of a chat. The channel itself for channel messages. The supergroup itself for messages from anonymous group administrators. The linked channel for messages automatically forwarded to the discussion group
  int date = 0; //	Date the message was sent in Unix time
  TelegramChat *chat; // Conversation the message belongs to
  TelegramUser *forward_from = NULL; // Optional. For forwarded messages, sender of the original message
  TelegramChat *forward_from_chat = NULL; // Optional. For messages forwarded from channels or from anonymous administrators, information about the original sender chat
  int forward_from_message_id = 0; // Optional. For messages forwarded from channels, identifier of the original message in the channel
  String forward_signature = ""; // Optional. For messages forwarded from channels, signature of the post author if present
  String forward_sender_name = ""; // Optional. Sender's name for messages forwarded from users who disallow adding a link to their account in forwarded messages
  int forward_date = 0; // 	Optional. For forwarded messages, date the original message was sent in Unix time
  struct TelegramMessage *reply_to_message = NULL; // Optional. For replies, the original message. Note that the Message object in this field will not contain further reply_to_message fields even if it itself is a reply.
  TelegramUser *via_bot = NULL; //	Optional. Bot through which the message was sent
  int edit_date = 0; //	Optional. Date the message was last edited in Unix time
  String media_group_id = ""; // Optional. The unique identifier of a media message group this message belongs to
  String author_signature = ""; // 	Optional. Signature of the post author for messages in channels, or the custom title of an anonymous group administrator
  String text = ""; // Optional. For text messages, the actual UTF-8 text of the message, 0-4096 character
  TelegramMessageEntity *entities = NULL; // <Array> Optional. For text messages, special entities like usernames, URLs, bot commands, etc. that appear in the text
  uint entities_size = 0; // sizeof entities array
  // TelegramAnimation *animation = NULL; // Optional. Message is an animation, information about the animation. For backward compatibility, when this field is set, the document field will also be set
  // TelegramAudio *audio = NULL; // Optional. Message is an audio file, information about the file
  // TelegramDocument *document = NULL; //	Optional. Message is a general file, information about the file
  // TelegramPhotoSize *photo = NULL; //	Optional. Message is a photo, available sizes of the photo
  // TelegramSticker *sticker = NULL; // Optional. Message is a sticker, information about the sticker
  // TelegramVideo *video = NULL; //	Optional. Message is a video, information about the video
  // TelegramVideoNote *video_note = NULL; // Optional. Message is a video note, information about the video message
  // TelegramVoice *voice = NULL; // Optional. Message is a voice message, information about the file
  String caption = ""; //	Optional. Caption for the animation, audio, document, photo, video or voice, 0-1024 characters
  TelegramMessageEntity *caption_entities = NULL; // <Array> Optional. For messages with a caption, special entities like usernames, URLs, bot commands, etc. that appear in the caption
  uint caption_entities_size = 0; // sizeof caption_entities
  // TelegramContact *contact = NULL; // Optional. Message is a shared contact, information about the contact
  // TelegramDice *dice = NULL; //	Optional. Message is a dice with random value
  // TelegramGame *game = NULL; //	Optional. Message is a game, information about the game.
  // TelegramPoll *poll = NULL; //	Optional. Message is a native poll, information about the poll
  // TelegramVenue *venue = NULL; // Optional. Message is a venue, information about the venue. For backward compatibility, when this field is set, the location field will also be set
  TelegramLocation *location = NULL; // Optional. Message is a shared location, information about the location
  TelegramUser *new_chat_members = NULL; // <Array>	Optional. New members that were added to the group or supergroup and information about them (the bot itself may be one of these members)
  uint new_chat_members_size = 0; // sizeof new_chat_members
  TelegramUser *left_chat_member = NULL; //	Optional. A member was removed from the group, information about them (this member may be the bot itself)
  String new_chat_title = ""; // Optional. A chat title was changed to this value
  // TelegramPhotoSize *new_chat_photo = NULL; //<Array> Optional. A chat photo was change to this value
  // uint new_chat_photo_size = 0; // sizeof new_chat_photo
  bool delete_chat_photo = false; // Optional. Service message: the chat photo was deleted
  bool group_chat_created = false; // Optional. Service message: the group has been created
  bool supergroup_chat_created = false; // Optional. Service message: the supergroup has been created. This field can't be received in a message coming through updates, because bot can't be a member of a supergroup when it is created. It can only be found in reply_to_message if someone replies to a very first message in a directly created supergroup.
  bool channel_chat_created = false; // Optional. Service message: the channel has been created. This field can't be received in a message coming through updates, because bot can't be a member of a channel when it is created. It can only be found in reply_to_message if someone replies to a very first message in a channel.
  // TelegramMessageAutoDeleteTimerChanged *message_auto_delete_timer_changed = NULL; // Optional. Service message: auto-delete timer settings changed in the chat
  int64_t migrate_to_chat_id = 0; // Optional. The group has been migrated to a supergroup with the specified identifier. This number may have more than 32 significant bits and some programming languages may have difficulty/silent defects in interpreting it. But it has at most 52 significant bits, so a signed 64-bit integer or double-precision float type are safe for storing this identifier.
  int64_t migrate_from_chat_id = 0; // 	Optional. The supergroup has been migrated from a group with the specified identifier. This number may have more than 32 significant bits and some programming languages may have difficulty/silent defects in interpreting it. But it has at most 52 significant bits, so a signed 64-bit integer or double-precision float type are safe for storing this identifier.
  TelegramMessage *pinned_message = NULL; //Optional. Specified message was pinned. Note that the Message object in this field will not contain further reply_to_message fields even if it is itself a reply.
  // TelegramInvoice *invoice = NULL; // Optional. Message is an invoice for a payment, information about the invoice. More about payments »
  // TelegramSuccessfulPayment *successful_payment = NULL; // 	Optional. Message is a service message about a successful payment, information about the payment. More about payments »
  String connected_website = ""; // Optional. The domain name of the website on which the user has logged in.
  // TelegramPassportData *passport_data = NULL; // Optional. Telegram Passport data
  // TelegramProximityAlertTriggered *proximity_alert_triggered = NULL; //	Optional. Service message. A user in the chat triggered another user's proximity alert while sharing Live Location.
  // TelegramVoiceChatScheduled *voice_chat_scheduled = NULL; //	Optional. Service message: voice chat scheduled
  // TelegramVoiceChatStarted *voice_chat_started = NULL; // Optional. Service message: voice chat started
  // TelegramVoiceChatEnded *voice_chat_ended = NULL; // Optional. Service message: voice chat ended
  // TelegramChatParticipantInvited *voice_chat_participants_invited = NULL; // Optional. Service message: new participants invited to a voice chat
  // TelegramInlineKeyboardMarkup *reply_markup = NULL; // Optional. Inline keyboard attached to the message. login_url buttons are represented as ordinary url buttons.
  int update_id = 0;

  ~TelegramMessage();

  TelegramMessage* fromJsonObject(JsonObject jsonObject);
};

struct TelegramInlineQuery {
  String id = ""; // Unique identifier for this query
  TelegramUser *from; // Sender
  String query = ""; // Text of the query (up to 256 characters)
  String offset = ""; // Offset of the results to be returned, can be controlled by the bot
  String chat_type = ""; // Optional. Type of the chat, from which the inline query was sent. Can be either “sender” for a private chat with the inline query sender, “private”, “group”, “supergroup”, or “channel”. The chat type should be always known for requests sent from official clients and most third-party clients, unless the request was sent from a secret chat
  TelegramLocation *location = NULL;

  ~TelegramInlineQuery();
};

struct TelegramCallbackQuery {
  String id = ""; // Unique identifier for this query
  TelegramUser *from = NULL; // Sender
  TelegramMessage *message = NULL; // Optional. Message with the callback button that originated the query. Note that message content and message date will not be available if the message is too old
  String inline_message_id = ""; //	Optional. Identifier of the message sent via the bot in inline mode, that originated the query.
  String chat_instance = ""; // Global identifier, uniquely corresponding to the chat to which the message with the callback button was sent. Useful for high scores in games.
  String data = ""; // Optional. Data associated with the callback button. Be aware that a bad client can send arbitrary data in this field.
  String game_short_name = ""; // Optional. Short name of a Game to be returned, serves as the unique identifier for the game

  ~TelegramCallbackQuery();

  TelegramCallbackQuery* fromJsonObject(JsonObject JsonObject);
};

struct TelegramChatMember {
  TelegramUser *user = NULL; // Information about the user
  String status = ""; // The member's status in the chat. Can be “creator”, “administrator”, “member”, “restricted”, “left” or “kicked”

  ~TelegramChatMember();
};

struct TelegramChatInviteLink {
  String invite_link = ""; // The invite link. If the link was created by another chat administrator, then the second part of the link will be replaced with “…”.
  TelegramUser *creator = NULL; // Creator of the link
  bool is_primary = false; // True, if the link is primary
  bool is_revoked = false; // True, if the link is revoked
  int expire_date = 0; // Optional. Point in time (Unix timestamp) when the link will expire or has been expired
  int member_limit = 0; // Optional. Maximum number of users that can be members of the chat simultaneously after joining the chat via this invite link; 1-99999

  ~TelegramChatInviteLink();
};

struct TelegramChatMemberUpdated {
  TelegramChat *chat = NULL;
  TelegramUser *user = NULL;
  int date = 0;
  TelegramChatMember *old_chat_member = NULL;
  TelegramChatMember *new_chat_member = NULL;
  TelegramChatInviteLink *invite_link = NULL;

  ~TelegramChatMemberUpdated();
};

struct TelegramUpdate {
  int update_id = 0;    // The update's unique identifier. 
  TelegramMessage *message = NULL; // Optional. New incoming message of any kind — text, photo, sticker, etc.
  TelegramMessage *edited_message = NULL; // Optional. New version of a message that is known to the bot and was edited
  TelegramMessage *channel_post = NULL; // 	Optional. New incoming channel post of any kind — text, photo, sticker, etc.
  TelegramMessage *edited_channel_post = NULL; // Optional. New version of a channel post that is known to the bot and was edited
  TelegramInlineQuery *inline_query = NULL; // Optional. New incoming inline query
  // TelegramChosenInlineResult *chosen_inline_result = NULL; // Optional. The result of an inline query that was chosen by a user and sent to their chat partner. Please see our documentation on the feedback collecting for details on how to enable these updates for your bot.
  TelegramCallbackQuery *callback_query = NULL; //	Optional. New incoming callback query
  // TelegramShippingQuery *shipping_query = NULL; // 	Optional. New incoming shipping query. Only for invoices with flexible price
  // TelegramPreCheckoutQuery *pre_checkout_query = NULL; // Optional. New incoming pre-checkout query. Contains full information about checkout
  // TelegramPoll *poll = NULL; //	Optional. New poll state. Bots receive only updates about stopped polls and polls, which are sent by the bot
  // TelegramPollAnswer *poll_answer = NULL; // Optional. A user changed their answer in a non-anonymous poll. Bots receive new votes only in polls that were sent by the bot itself.
  // TelegramChatMemberUpdated	*my_chat_member = NULL; // Optional. The bot's chat member status was updated in a chat. For private chats, this update is received only when the bot is blocked or unblocked by the user.
  // TelegramChatMemberUpdated *chat_member = NULL; // Optional. A chat member's status was updated in a chat. The bot must be an administrator in the chat and must explicitly specify “chat_member” in the list of allowed_updates to receive these updates.

  ~TelegramUpdate();
};

#endif
