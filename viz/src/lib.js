module.exports = {
  client: {
    _connected: false,
    set connected(state) {
      this.__connected = state;
    },
    get connected() {
      return this.__connected;
    }
  },
  MIMETypes: {
    'html': 'text/html',
    'css': 'text/css',
    'js': 'text/javascript; charset=utf-8',
    'svg': 'image/svg+xml',
    'ico': 'image/x-icon'
  },
  getLine: (function () {
    const cache = new Map();

    return function(key, data) {
      let cached = (cache.get(key) ?? "") + (data ?? "");
      let result;
      if (cached.includes('\n')) {
        cached = cached.split("\n");
        result = cached.shift();
        cached = cached.join("\n");
        cache.set(key, cached);
      } else if (data?.length) {
        cache.set(key, data);
      }
      return result;
    }
  })(),
  say: (function() {
    try {
      const synth = window.speechSynthesis;
      const utter = new SpeechSynthesisUtterance();

      return function(text) {
        utter.text = text;
        synth.speak(utter);
      }
    } catch(err) {
      console.log("[say] " + err.message);
    }
  })(),
  sleep: function(time) {
    return new Promise(resolve => {
      setTimeout(() => resolve("ok"), time);
    });
  }
}