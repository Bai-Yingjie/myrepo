package main

import (
    "flag"
    "os"
    "encoding/json"
    "io/ioutil"
)

var loopNum = flag.Int("loopNum", 1, "loops to run")
var fileName = flag.String("fileName", "test.json", "name of the json file")

func loadJsonAndDump(fileName string) {
    f, err := ioutil.ReadFile(fileName)
    if err != nil {
        panic(err)
    }

    var result map[string]interface{}
    json.Unmarshal(f, &result)

    out, _ := json.Marshal(&result)

    os.Stdout.Write(out)
}

func main() {
    flag.Parse()
    count := *loopNum
    fname := *fileName

    for i := 0; i < count; i++ {
        loadJsonAndDump(fname)
    }
}

