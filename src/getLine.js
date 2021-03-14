module.exports = (function () {
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
})();