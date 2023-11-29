import spotipy
from spotipy.oauth2 import SpotifyOAuth
from pprint import pprint

scope = "user-library-read, user-read-playback-state, user-modify-playback-state"
sp = spotipy.Spotify(client_credentials_manager=SpotifyOAuth(scope=scope))

isPlaying = True
res = sp.devices()
pprint(res)

print("Welcome to the project")
while isPlaying:
  if y_predicted == 1: 
    print("Song is played")
    sp.start_playback(uris=['spotify:track:1fDFHXcykq4iw8Gg7s5hG9'])
    isPlaying = False
  elif y_predicted == 0:
    print("Song is paused")
    sp.pause_playback()
    isPlaying = False
  elif y_predicted == 2:
    print("Good Bye, Have a great day!")
    sp.next_track()
    isPlaying = False
    break