Table user {
  user_id serial [PK, not null]
  username str [not null]
  role str [not null]
}

Table video {
  video_id serial [PK, not null]
  hash str [not null]
  filename str [not null]
  description text
  user_id int [ref: > user.user_id, not null]
}
