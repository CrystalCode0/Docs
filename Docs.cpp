#include<iostream>
#include<vector>
#include<string>
#include<fstream>
using namespace std;

class render_element
{
 public:
 virtual string render()=0;
};

class text:public render_element
{
 private:
 string s;
 public:
 text(string s)
 {
    this->s=s;
 }
 string render()
 {
    return s;
 }
 ~text()
 {
    cout<<"DESTROYED TEXT"<<endl;
 }
};

class image:public render_element
{
 private:
 string s;
 public:
 image(string s)
 {
    this->s=s;
 }
 string render()
 {
    return s;
 }
 ~image()
 {
    cout<<"DESTROYED IMAGE"<<endl;
 }
};

class document
{
 private:
 vector<render_element*> elements;
 public:
   void add_element(render_element*ptr)
   {
     elements.push_back(ptr);
   }
  string render()
  { 
    string result;
    for(auto i:elements)
    {
        result+=i->render();
    }
    return result;
  }
};

class Persistence{
public:
virtual void save(string data)=0;
};

class filestorage:public Persistence
{
    public:
          void save(string data)
          {
            ofstream outFile("document.txt");
            if(outFile)
            { outFile << data;
                outFile.close();
                cout<<"Document saved to document.txt";
            }
            else{
                cout<<"Error:Unable to open file for writing"<<endl;
            }
          }
};

class Dbstorage:  public Persistence{
    public:
    void save(string data)
    {
        //save to db
    }
};

class DocumentEditor
{   
    private:
    document*dc;
    Persistence*storage;
    string renderdocument;

    public:
    DocumentEditor(document* document,Persistence *storage)
    {
        this->dc=document;
         this->storage=storage;
    }

    void add_text(string s)
    {
     dc->add_element(new text(s));
    }

    void add_image(string s)
    {
     dc->add_element(new image(s));
    }

    string renderDocument()
    {
        if(renderdocument.empty())
        {
         renderdocument=dc->render();
        }
        return renderdocument;
    }
    void savedocument()
    {
        storage->save(renderDocument());
    }
};

int main()
{
    document*dc=new document();
    Persistence*storage=new filestorage();

    DocumentEditor* editor= new DocumentEditor(dc,storage);
    editor->add_text("Congratulations vaibhav for your first project\n");
    editor->add_image("Image.png");

    cout<<editor->renderDocument()<<endl;
    editor->savedocument();
    return 0;
}
