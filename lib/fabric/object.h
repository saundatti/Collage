
/* Copyright (c) 2009-2010, Stefan Eilemann <eile@equalizergraphics.com> 
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 2.1 as published
 * by the Free Software Foundation.
 *  
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef EQFABRIC_OBJECT_H
#define EQFABRIC_OBJECT_H

#include <eq/fabric/serializable.h> // base class
#include <eq/net/objectVersion.h>   // member

namespace eq
{
namespace fabric
{
    /**
     * Base class for all distributed, inheritable Equalizer objects.
     *
     * This class provides common data storage used by all Equalizer resource
     * entities.
     */
    class Object : public fabric::Serializable
    {
    public:
        /** @name Data Access. */
        //@{
        /** Set the name of the object. @version 1.0 */
        EQ_EXPORT void setName( const std::string& name );

        /** @return the name of the object. @version 1.0 */
        EQ_EXPORT const std::string& getName() const;

        /**
         * Set user-specific data.
         *
         * The application is responsible to register the master version of the
         * user data object. Commit, sync and Session::mapObject of the user
         * data object are automatically executed when commiting and syncing
         * this object. Not all instances of the object have to set a user data
         * object. All instances have to set the same type of object.
         * @version 1.0
         */
        EQ_EXPORT void setUserData( net::Object* userData );

        /** @return the user-specific data. @version 1.0 */
        net::Object* getUserData() { return _userData; }

        /** @return the user-specific data. @version 1.0 */
        const net::Object* getUserData() const { return _userData; }
        //@}

        /** @name Error Information. */
        //@{
        /** 
         * Set a message why the last operation failed.
         * 
         * The message will be transmitted to the originator of the request, for
         * example to Config::init when set from within configInit().
         *
         * @param message the error message.
         * @version 1.0
         */
        EQFABRIC_EXPORT void setErrorMessage( const std::string& message );

        /** @return the error message from the last operation. */
        const std::string& getErrorMessage() const { return _error; }
        //@}

        /** @name Data Access */
        //@{
        /** 
         * Return the set of tasks this channel might execute in the worst case.
         * 
         * It is not guaranteed that all the tasks will be actually executed
         * during rendering.
         * 
         * @return the tasks.
         * @warning Experimental - may not be supported in the future
         */
        uint32_t getTasks() const { return _tasks; }
        //@}

        /** @return true if the view has data to commit. @version 1.0 */
        EQ_EXPORT virtual bool isDirty() const;

        /**
        * The changed parts of the object since the last pack().
        *
        * Subclasses should define their own bits, starting at DIRTY_CUSTOM.
        */
        enum DirtyBits
        {
            DIRTY_NAME       = Serializable::DIRTY_CUSTOM << 0,
            DIRTY_USERDATA   = Serializable::DIRTY_CUSTOM << 1,
            DIRTY_ERROR      = Serializable::DIRTY_CUSTOM << 2,
            DIRTY_TASKS      = Serializable::DIRTY_CUSTOM << 3,
            // Leave room for binary-compatible patches
            DIRTY_CUSTOM     = Serializable::DIRTY_CUSTOM << 6 // 64
        };

        EQ_EXPORT virtual uint32_t commitNB(); //!< @internal

        /** Back up app-specific data, excluding child data. @internal */
        EQFABRIC_EXPORT virtual void backup();

        /** Restore the last backup. @internal */
        EQFABRIC_EXPORT virtual void restore();

    protected:
        /** Construct a new Object. */
        EQ_EXPORT Object();
        
        /** Destruct the object. */
        EQ_EXPORT virtual ~Object();

        /**
         * @return true if this instance shall hold the master instance of the
         *         user data object, false otherwise.
         */
        virtual bool hasMasterUserData() { return false; }

        /** Set the tasks this entity might potentially execute. @internal */
        void EQFABRIC_EXPORT setTasks( const uint32_t tasks );

        EQ_EXPORT virtual void notifyDetach();

        EQ_EXPORT virtual void serialize( net::DataOStream& os,
                                          const uint64_t dirtyBits );

        EQ_EXPORT virtual void deserialize( net::DataIStream& is, 
                                            const uint64_t dirtyBits );

    private:
        struct BackupData
        {
            /** The application-defined name of the object. */
            std::string name;

            /** The user data parameters if no _userData object is set. */
            net::ObjectVersion userData;
        }
            _data, _backup;

        /** The user data. */
        net::Object* _userData;

        /** Worst-case set of tasks. */
        uint32_t _tasks;

        /** The reason for the last error. */
        std::string _error;

        union // placeholder for binary-compatible changes
        {
            char dummy[8];
        };
    };
}
}
#endif // EQFABRIC_OBJECT_H
