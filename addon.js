var addon = require('bindings')('addon');
const {
    Worker, isMainThread, parentPort, workerData
} = require('worker_threads');
/*
function createWorker(count) {
    return new Promise((resolve, reject) => {
        const worker = new Worker(__filename, {
            workerData: count
        });
        worker.on('message', resolve);
        worker.on('error', reject);
        worker.on('exit', (code) => {
            if (code !== 0)
                reject(new Error(`Worker stopped with exit code ${code}`));
        });
    });
};

if (isMainThread) {
    createWorker(1);
    createWorker(2);
} else {
    
}
*/

obj1 = addon.MyObject(1);
while(true)
    obj1.createObject(1);