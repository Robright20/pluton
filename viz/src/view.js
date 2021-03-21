const peter = require('puppeteer');

(async () => {
  const browser = await peter.launch({ headless: false });
  const page = await browser.newPage();
  await page.setViewport({
    width: 954,
    height: 1306,
    deviceScaleFactor: 1
  });
  await page.goto('http://localhost:3000');
// "954*1306"
  // Get the "viewport" of the page, as reported by the page.
  await browser.close();
})();