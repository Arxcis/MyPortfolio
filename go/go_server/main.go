package main

import (
    //"fmt"
    "io"
    "net/http"
    "html/template"
    "os"
    "io/ioutil"
)

func main() {
    var templates *template.Template
    var err error

    //
    // Parse all template files into a cache
    //
    {
        // Get file handles from template directory
        var files []os.FileInfo
        files, err = ioutil.ReadDir("./templates")
        if err != nil {
            panic(err)
        }

        // Grab all file names, and store in string array
        var allFilenames []string
        for _, file := range files {
            filename := file.Name()
            allFilenames = append(allFilenames, "./templates/" + filename)
        }

        // Parses all .tmpl files in the template directory
        templates, err = template.ParseFiles(allFilenames...)
        if err != nil {
            panic(err)
        }
    }

    //
    //  Setting up http routes
    //
    {
        var mux *http.ServeMux = http.NewServeMux()  // Creating a HTTP request multiplexer

        mux.HandleFunc("/",
            func (w http.ResponseWriter, r *http.Request) {
                w.Header().Set("Content-Type", "text/html")

                var t *template.Template = templates.Lookup("index.tmpl")
                t.ExecuteTemplate(w, "index", nil)
            })

        mux.HandleFunc("/home",
            func (w http.ResponseWriter, r *http.Request) {
                io.WriteString(w, "<h1>Page 2</h1>")
            })

        http.ListenAndServe(":5000", mux)
    }
}
