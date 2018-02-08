const NApiSandbox = require("../lib/binding.js");

const demo = () => {
  const instance = new NApiSandbox("Miss Piggy");

  instance.greet("Kermit the Frog")
    .then((value) => {
      console.log("promise returned", value, "!");
    }).catch((err) => {
      console.log(`[ERROR]: ${err}`);
    });

  new Promise(function(resolve) {
    setTimeout(resolve, 10000);
  }).then(() => {
    console.log('finished');
  });
  console.log("timeout set");
};

demo();
