#include <list>
#include <gtk/gtk.h>

gint _onDeleteEvent(GtkWidget *widget, GdkEvent *event, gpointer data);

struct point
{
   int x;
   int y;
   
   point(int a, int b): x(a), y(b) {}      
};

typedef std::list<point> list_of_points;

struct AfficheVilles
{
    /* GtkWidget est le type pour declarer les widgets. */
    static GtkWidget* m_window;
    static GdkPixmap* m_pixmap;
    static bool m_configure;
    static list_of_points m_points;
 
    // Cette fonction est appelee dans toutes les applications GTK. 
    // Les parametres passes en ligne de commande sont analyses et 
    // retournes a l'application. 
     static void init(char** theArguments, int theArgumentCount)
     {
        gtk_init (&theArgumentCount, &theArguments);
        m_window = NULL;
        m_pixmap = NULL;
        m_configure = false;
     }
 
     /* Creation d'une nouvelle fenetre. */
    static void create(const list_of_points& thePoints)
    {
          m_points = thePoints;
          m_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
          
         /* Lorsque la fenetre reeoit le signal "delete_event" 
          * (envoye par le gestionnaire de fenetres en utilisant l'option
          * e close e ou la barre de titre), on lui demande d'appeler la
          * fonction delete_event() definie plus haut. La donnee passee en
          * parametre e la fonction de rappel est NULL et est ignore dans le
          * rappel. */
     
         gtk_signal_connect (GTK_OBJECT (m_window), "delete_event",
                             GTK_SIGNAL_FUNC (onDeleteEvent), NULL);
                             
         gtk_signal_connect (GTK_OBJECT (m_window), "destroy_event",
                             GTK_SIGNAL_FUNC (onDestroyEvent), NULL);

                             // Ici, on connecte l'evenement "destroy" e un gestionnaire de signal.
         // Cet evenement arrive lorsqu'on appelle gtk_widget_destroy() sur la
         // fenetre, ou si l'on retourne TRUE dans le rappel "delete_event". 
     
         gtk_signal_connect (GTK_OBJECT (m_window), "configure_event",
                             GTK_SIGNAL_FUNC (onConfigureEvent), NULL);

         gtk_signal_connect (GTK_OBJECT (m_window), "expose_event",
                             GTK_SIGNAL_FUNC (onExposeEvent), NULL);

         // Configuration de la largeur du contour de la fenetre.
         gtk_container_border_width (GTK_CONTAINER (m_window), 10);
    }

    // Affiche la fenetre et attand que l'utilisateur la ferme
    static void showAndWait()
    {
         // Affiche la fenetre 
         gtk_widget_show (m_window);
         /* Toutes les applications GTK doivent avoir un gtk_main(). 
          * Le deroulement du programme se termine le et attend qu'un
          * evenement survienne (touche pressee ou evenement souris). */
         gtk_main ();
    }

    static void releaseResources()
    {
        if(m_pixmap != NULL) 
            gdk_pixmap_unref(m_pixmap);
         m_pixmap = NULL;
         m_window = NULL;
    }
         
     // La fenetre notifie l'evenement "delete"
    static void onDeleteEvent(GtkWidget *widget, GdkEvent *event, gpointer data)
    {
         /* Si l'on renvoit TRUE dans le gestionnaire du signal "delete_event",
          * GTK emettra le signal "destroy". Retourner FALSE signifie que l'on
          * ne veut pas que la fenetre soit detruite. 
          * Utilise pour faire apparaetre des boetes de dialogue du type
          * e etes-vous ser de vouloir quitter ? e */
     
         /* Remplacez FALSE par TRUE et la fenetre principale sera detruite par
          * un signal e delete_event e. */
         releaseResources();
         gtk_main_quit ();
    }
     
     // La fenetre notifie l'evenement "destroy"
    static void onDestroyEvent (GtkWidget *widget, gpointer data)
    {
         releaseResources();
         gtk_main_quit ();
    }
 
    // Creation d'un nouveau pixmap d'arrière-plan de la taille voulue
    static gint onConfigureEvent(GtkWidget *widget, GdkEventConfigure *event)
    {
        // Lecture du fichier servant de base au pixmap.
        m_pixmap = gdk_pixmap_create_from_xpm(
            m_window->window, NULL, NULL, "./france.xpm");
     
        // Dimensionnement de la fenêtre en fonction du fichier 
        gdk_window_resize(m_window->window, 658, 669);        

        list_of_points::iterator end = m_points.end();
        list_of_points::iterator first = m_points.begin();
        if(first != end)
        {
            list_of_points::iterator second = m_points.begin();
            second ++;
            while(second != end)
            {
                gdk_draw_line(m_pixmap, m_window->style->black_gc, first->x, first->y, second->x, second->y);
                first ++;
                second ++;
            }
        }
        
        gdk_draw_pixmap(m_window->window,
                        m_window->style->fg_gc[GTK_WIDGET_STATE (m_window)],
                        m_pixmap,
                        0, 0, 
                        0, 0, 656, 667);
        m_configure = true;
        return TRUE;
    }

    static gint onExposeEvent(GtkWidget *widget, GdkEventExpose *event)
    {
        if(m_pixmap != NULL)
        {
            gdk_draw_pixmap(widget->window,
                            widget->style->fg_gc[GTK_WIDGET_STATE (widget)],
                            m_pixmap,
                            event->area.x, event->area.y,
                            event->area.x, event->area.y,
                            event->area.width, event->area.height);
        }
        return FALSE;
    }

};


