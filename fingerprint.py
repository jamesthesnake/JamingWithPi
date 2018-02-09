from subprocess import Popen, PIPE
import urllib
import urllib2
import json
import requests
import pdb

base_dir = '/home/pi/jambox/'
ex_dir = base_dir + 'rpi_gnsdk/examples/'
username = 'e0ecaa461521bababe8be4c363d4b2af'
api_base = None #should point to Oscar's rest-ws API...

def record():
    out_file = ex_dir + 'data/tmp.wav' 
    cmd = ['timeout','5','arecord','-f','S32_LE','-D','plughw:1,0','-r','44100',out_file]
    res = Popen(cmd,stderr=PIPE,stdout=PIPE)
    out,err = res.communicate()

def fingerprint():
    script = ex_dir + 'lookup.sh'
    cmd = [script]
    res = Popen(cmd,stdout=PIPE,stderr=PIPE)
    out,err = res.communicate()
    out = out.strip()
    print out
    
    out = out.split('\t')
    if len(out) != 2:
        return None
    
    return ' '.join(out) # ask oscar if you can search for artist and track

def lookup_song_id(song):
    # lookup track
    params = {'limit':'1','field':'uri_spotify','q':song,'format':'json'}
    query_str = urllib.urlencode(params.items())
    url = api_base + "track/search?" + query_str
    res = json.loads(urllib2.urlopen(url).read())
    return res['response'][0]['id']

def create_station(song_id):
    url = api_base + 'user/' + username + '/station/track/' + song_id
    resp = requests.put(url)
    if not resp.ok:
        return None
    return resp.text

def get_station_tracks(station_id):
    url = api_base + 'user/' + username + '/station/' + station_id
    params = {'field':'uri_spotify','limit':5,'format':'json'}
    resp = requests.get(url,params=params) 
    resp = resp.json
    lst = []
    if not resp or 'response' not in resp:
        print url
        print resp.status_code
        print resp.text
        return lst
    for pyob in resp['response']:
        lst.append(pyob['metadata']['uri_spotify'])
    return lst

def fp_to_tracks():
    record()
    match = fingerprint()
    if not match:
        print "whoopsie"
        return []
    song_id = lookup_song_id(match)
    station_id = create_station(song_id)
    if not station_id:
        return []
    return  get_station_tracks(station_id)

if __name__=="__main__":
    print fp_to_tracks()
