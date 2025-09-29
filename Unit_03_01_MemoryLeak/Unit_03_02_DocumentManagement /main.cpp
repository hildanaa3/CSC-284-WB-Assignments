#include <iostream>
#include <memory>
#include <string>

using namespace std;

class Document {
    string title;
    unique_ptr<string> content;

public:
    Document(const string& t, const string& c)
        : title(t), content(unique_ptr<string>(new string(c))) {
        cout << "Document \"" << title << "\" created." << endl;
    }

    ~Document() {
        cout << "Document \"" << title << "\" destroyed." << endl;
    }

    void show() const {
        cout << "Title: " << title << endl;
        cout << "Content: " << *content << endl;
    }

    void edit(const string& newContent) {
        *content = newContent;
    }
};

// helper functions
unique_ptr<Document> createDocument(const string& t, const string& c) {
    return unique_ptr<Document>(new Document(t, c));
}

shared_ptr<Document> createSharedDocument(const string& t, const string& c) {
    return make_shared<Document>(t, c);
}

int main() {
    cout << "=== Unique_ptr demonstration ===\n";
    unique_ptr<Document> doc1 = createDocument("My Unique Doc", "Initial content");
    doc1->show();

    // Transfer ownership
    unique_ptr<Document> doc2 = std::move(doc1);
    if (!doc1) {
        cout << "doc1 no longer owns the document\n";
    }
    doc2->edit("Updated content");
    doc2->show();

    cout << "\n=== Shared_ptr demonstration ===\n";
    shared_ptr<Document> sharedDoc = createSharedDocument("Shared Doc", "Shared content");
    {
        shared_ptr<Document> viewer = sharedDoc;  // second owner
        viewer->show();
        viewer->edit("Edited by viewer");
    } // viewer goes out of scope

    sharedDoc->show();
    cout << "End of main()\n";

    return 0;
}

