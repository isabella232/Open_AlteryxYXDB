const NApiSandbox = require("../lib/binding.js").NApiSandbox;
const assert = require("assert");

assert(NApiSandbox, "The expected module is undefined");

async function testBasic()
{
    const instance = new NApiSandbox("mr-yeoman");
    assert(instance.greet, "The expected method is not defined");
    await instance.greet("kermit").then((e, value) => {
        console.log("promise returned!");
        assert.strictEqual(value, "mr-yeoman", "Unexpected value returned");
    });
}

function testInvalidParams()
{
    const instance = new NApiSandbox();
}

assert.doesNotThrow(testBasic, undefined, "testBasic threw an expection");
assert.throws(testInvalidParams, undefined, "testInvalidParams didn't throw");

console.log("js: Tests passed- everything looks OK!");
